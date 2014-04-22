#pragma once

namespace ShellLib { namespace Workspaces {

	using IEnum = System::Collections::IEnumerable;
	using IEtor = System::Collections::IEnumerator;
	using namespace System::Collections::Generic;

	ref class CWorkspaceCollection : public IList<ShellLib::Workspaces::IWorkspace ^>
	{
	public:		//	Poperties
		property virtual int		Count { int get(void); }
		property virtual bool		IsReadOnly { bool get(void); }
		property virtual IWorkspace ^ default[int] { IWorkspace ^ get(int index); void set(int index, IWorkspace ^ value); }

	public:		//	Operations
		virtual void				Add(IWorkspace ^ item);
		virtual void				Clear(void);
		virtual bool				Contains(IWorkspace ^ item);
		virtual void				CopyTo(array<IWorkspace ^> ^ array, int arrayIndex);
		virtual IEtor ^				GetEnumerator0(void) = IEnum::GetEnumerator;
		virtual IEnumerator<IWorkspace ^> ^ GetEnumerator(void) = IList<IWorkspace ^>::GetEnumerator;
		virtual int					IndexOf(IWorkspace ^ item);
		virtual void				Insert(int index, IWorkspace ^ item);
		virtual bool				Remove(IWorkspace ^ item);
		virtual void				RemoveAt(int index);
	};

}}