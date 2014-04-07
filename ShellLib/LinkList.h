#pragma once

namespace Unmanaged {

	template <typename T>
	class CLinkList abstract
	{
	protected:
		//template <typename T> 
		CLinkList(void);
		//template <typename T> 
		CLinkList(const T & head);

	public:
		//template <typename T> 
		void Push(const T & value);
		//template <typename T> 
		T & Pop(void);

	protected:
		//template <typename T> 
		void	PushValue(const T & value) abstract;
		//template <typename T> 
		T &		PopValue(void) abstract;
		//template <typename T> 
		CNode *		GetTrailNode() {};

	private:
		CNode * m_head;
	};
}