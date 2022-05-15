#ifndef _Template_H_
#define _Template_H_

class TemplateBase
{
	public:
		virtual ~TemplateBase();
		void TemplateMethod();

	protected:
		virtual void Operation1() = 0;
		virtual void Operation2() = 0;
		TemplateBase();

	private:
};

class Template1 : public TemplateBase
{
	public:
		Template1();
		~Template1();

	protected:
		void Operation1();
		void Operation2();

	private:
};
	
class Template2 : public TemplateBase
{
	public:
		Template2();
		~Template2();

	protected:
		void Operation1();
		void Operation2();

	private:
};


#endif //~ Template H
	