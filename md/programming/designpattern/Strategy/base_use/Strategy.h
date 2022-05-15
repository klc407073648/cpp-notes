#ifndef _STRATEGY_H_
#define _STRATEGY_H_
class StrategyBase
{
	public:
		StrategyBase();
		virtual ~StrategyBase();
		virtual void AlgrithmInterface() = 0;

	protected:
	private:
};

class StrategyA : public StrategyBase
{
	public:
		StrategyA();
		virtual ~StrategyA();
		void AlgrithmInterface();

	protected:
	private:
};

class StrategyB : public StrategyBase
{
	public:
		StrategyB();
		virtual ~StrategyB();
		void AlgrithmInterface();

	protected:
	private:
};

#endif //~_STRATEGY_H_