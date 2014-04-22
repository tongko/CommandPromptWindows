#pragma once

namespace ShellLib { namespace Workspaces {

	using IEnum = System::Collections::IEnumerable;
	using IEtor = System::Collections::IEnumerator;
	using namespace System::Collections::Generic;

	ref class CWorkspaceCollection : public IList<ShellLib::Workspaces::IWorkspace ^>
	{
	public:		//	Poperties
		property virtual int		Count { int get(void) override; }
		property virtual bool		IsReadOnly { bool get(void) override; }
		property virtual IWorkspace ^ Item[int] { IWorkspace ^ get(int index) override; void set(int index, IWorkspace ^ value) override; }

	public:		//	Operations
		virtual void				Add(IWorkspace ^ item) override;
		virtual void				Clear(void) override;
		virtual bool				Contains(IWorkspace ^ item) override;
		virtual void				CopyTo(array<IWorkspace ^> ^ array, int arrayIndex) override;
		virtual IEtor ^				GetEnumerator0(void) = IEnum::GetEnumerator;
		virtual IEnumerator<IWorkspace ^> ^ GetEnumerator(void) = IList<IWorkspace ^>::GetEnumerator;
		virtual int					IndexOf(IWorkspace ^ item);
		virtual void				Insert(int index, IWorkspace ^ item) override;
		virtual bool				Remove(IWorkspace ^ item) override;
		virtual void				RemoveAt(int index) override;
	};

}}