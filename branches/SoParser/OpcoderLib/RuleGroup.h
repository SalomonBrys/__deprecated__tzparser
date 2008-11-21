#ifndef __SO_RULE_GROUP_H__
#define __SO_RULE_GROUP_H__

#include "AutoPtr.h"
#include "Rule.h"

#include <deque>

namespace SoParse
{
	typedef SoUtil::AutoPtr<IRule>	APIRule;
	typedef std::deque<APIRule>		DequeAPIRule;

	class RuleGroup : public DequeAPIRule, public IRule
	{
	public:
		virtual ~RuleGroup() {}

		virtual char const * getType() const { return "group"; }

		virtual APIRule	groupizeAND(APIRule self, APIRule r)
		{
			this->push_back(r);
			return self;
		}

		virtual APIRule	groupizeOR(APIRule self, APIRule r)
		{
			this->push_back(r);
			return self;
		}

		virtual void	acceptVisitor(IRulesVisitor * visitor)
		{
			visitor->enter(this);
			for (RuleGroup::iterator i = this->begin(); i != this->end(); ++i)
			{
				(*i)->acceptVisitor(visitor);
			}
			visitor->leave(this);
		}
	};

	typedef SoUtil::AutoPtr<RuleGroup> APRuleGroup;

	class RuleGroupAND : public RuleGroup
	{
	public:
		virtual ~RuleGroupAND() {}
		virtual std::string getName() const { return "_GroupAND"; }

		virtual std::string	getOpcodeStart() { return ""; }
		virtual std::string	getOpcodeEnd() { return ""; }
	};

	class RuleGroupOR : public RuleGroup
	{
	public:
		virtual ~RuleGroupOR() {}
		virtual std::string getName() const { return "_GroupOR"; }

		virtual std::string	getOpcodeStart() { return ""; }
		virtual std::string	getOpcodeEnd() { return ""; }
	};
}

#endif  // !__SO_RULE_GROUP_H__