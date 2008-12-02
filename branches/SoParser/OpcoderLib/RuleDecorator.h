#ifndef __SO_RULE_DECORATOR_H__
#define __SO_RULE_DECORATOR_H__

#include "Rule.h"
#include "AutoPtr.h"

namespace SoParse
{
	class RuleDecorator : public IRule
	{
	public:
		virtual ~RuleDecorator() {}

		virtual IRule::type getType() const { return IRule::INTERNAL; }

		virtual APIRule	groupizeAND(APIRule self, APIRule r) { return _r->groupizeAND(self, r); }
		virtual APIRule	groupizeOR(APIRule self, APIRule r) { return _r->groupizeOR(self, r); }

		void	assign(APIRule r) { _r = r; }

		virtual bool	needRepeater() { return _r->needRepeater(); }

		virtual void	acceptVisitor(IRulesVisitor * visitor)
		{
			visitor->enter(this);
			_r->acceptVisitor(visitor);
			visitor->leave(this);
		}

	private:
		APIRule	_r;
	};

	APIRule operator << (APIRule r, RuleDecorator * d)
	{
		d->assign(r);
		return APIRule(d);
	}
}

#endif  // !__SO_RULE_DECORATOR_H__
