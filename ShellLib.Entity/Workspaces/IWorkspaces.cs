using ShellLib.Drawing;

namespace ShellLib.Workspaces
{
	public interface IWorkspace
	{
		CCoord Location { get; set; }
		CSize Size { get; set; }
		CRectangle ClientArea { get; set; }
		BorderStyleType BorderStyle { get; set; }
		string Caption { get; set; }
		int ZOrder { get; set; }
		bool MinimizeBox { get; set; }
		bool RestroreBox { get; set; }
		WorkspaceCollection Workspaces { get; set; }

		//	Operations
		void Activate();
		void Focus();
	}
}