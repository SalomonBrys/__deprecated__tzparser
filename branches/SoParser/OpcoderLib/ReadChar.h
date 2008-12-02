#ifndef __SO_READCHAR_H__
#define __SO_READCHAR_H__

#include "AtomicRule.h"
#include "Opcodes.h"

namespace SoParse
{
	class ReadAnyChar : public AtomicRule
	{
	public:
		virtual ~ReadAnyChar() {}
		ReadAnyChar() {}

		virtual std::string getName() const { return "GetChar"; }

		virtual OpcodePart *	getOpcodeStart(OpcoderInfos& infos) { return new OpcodePart(READ_CHAR); }
		virtual OpcodePart *	getOpcodeEnd(OpcoderInfos& infos) { return 0; }
	};

	inline APIRule ReadChar()
	{
		return APIRule(new ReadAnyChar);
	};

	class ReadAChar : public AtomicRule
	{
	public:
		virtual ~ReadAChar() {}
		ReadAChar(char c) : _c(c) {}

		virtual std::string getName() const { return std::string("GetChar(") + _c + ')'; }

		virtual OpcodePart *	getOpcodeStart(OpcoderInfos& infos) { return new OpcodePart(READ_A_CHAR, _c, 0); }
		virtual OpcodePart *	getOpcodeEnd(OpcoderInfos& infos) { return 0; }

	private:
		const char _c;
	};

	inline APIRule ReadChar(char c)
	{
		return APIRule(new ReadAChar(c));
	};

	class ReadCharRange : public AtomicRule
	{
	public:
		virtual ~ReadCharRange() {}

		ReadCharRange(char s, char e) : _s(s), _e(e) {}

		virtual std::string getName() const { return std::string("GetChar(") + _s + ", " + _e + ")"; }

		virtual OpcodePart *	getOpcodeStart(OpcoderInfos& infos) { return new OpcodePart(READ_CHAR_RANGE, _s, _e); }
		virtual OpcodePart *	getOpcodeEnd(OpcoderInfos& infos) { return 0; }

	private:
		const char _s;
		const char _e;
	};

	inline APIRule ReadChar(char s, char e)
	{
		return APIRule(new ReadCharRange(s, e));
	};
}

#endif  // !__SO_READCHAR_H__
