using System.Configuration;

namespace ShellLib.Configs
{
	public class CShellLibConfigSection : ConfigurationSection
	{
		public const string ShellConfigName = "ShellConfiguration";

		[ConfigurationProperty(ShellConfigName, IsRequired = false)]
		public CShellConfigElement ShellConfiguraiton
		{
			get { return (CShellConfigElement)this[ShellConfigName]; }
			set { this[ShellConfigName] = value; }
		}
	}
}
