using ShellLib.Workspaces;
using System.Configuration;

namespace ShellLib.Configs
{
	// <ShellConfiguration>
	//		<Layout windowLeft="0" windowTop="0">
	//			<WindowSize width="120" height="65" />
	//			<BufferSize width="120" height="65" />
	//		</Layout>
	// </ShellConfiguration>
	public class CShellConfigElement : ConfigurationElement
	{
		public const string CaptionName = "Caption";
		public const string LayoutName = "Layout";
		public const string CursorSizeName = "cursorSize";

		[ConfigurationProperty(CaptionName, IsRequired = false)]
		public string Caption
		{
			get { return (string)this[CaptionName]; }
			set { this[CaptionName] = value; }
		}

		[ConfigurationProperty(CursorSizeName, DefaultValue = CursorSizeEnum.Small, IsRequired = false)]
		public CursorSizeEnum CursorSize
		{
			get { return (CursorSizeEnum)this[CursorSizeName]; }
			set { this[CursorSizeName] = value; }
		}

		[ConfigurationProperty(LayoutName)]
		public CShellLayoutConfigElement Layout
		{
			get { return (CShellLayoutConfigElement)this[LayoutName]; }
			set { this[LayoutName] = value; }
		}
	}

	public class CShellLayoutConfigElement : ConfigurationElement
	{
		public const string WindowSizeName = "WindowSize";
		public const string ScreenBuffSizeName = "BufferSize";
		public const string WindowLeftName = "windowLeft";
		public const string WindowTopName = "windowTop";
		public const string MaxWindowName = "maxWindow";

		[ConfigurationProperty(MaxWindowName, DefaultValue = false, IsRequired = false)]
		public bool MaxWindow
		{
			get { return (bool)this[MaxWindowName]; }
			set { this[MaxWindowName] = value; }
		}

		[ConfigurationProperty(WindowLeftName, DefaultValue = -4, IsRequired = false)]
		public int WindowLeft
		{
			get { return (int)this[WindowLeftName]; }
			set { this[WindowLeftName] = value; }
		}

		[ConfigurationProperty(WindowTopName, DefaultValue = -4, IsRequired = false)]
		public int WindowTop
		{
			get { return (int)this[WindowTopName]; }
			set { this[WindowTopName] = value; }
		}

		[ConfigurationProperty(WindowSizeName, IsRequired = false)]
		public CShellLayoutSizeConfigElement WindowSize
		{
			get { return (CShellLayoutSizeConfigElement)this[WindowSizeName]; }
			set { this[WindowSizeName] = value; }
		}

		[ConfigurationProperty(ScreenBuffSizeName, IsRequired = false)]
		public CShellLayoutSizeConfigElement ScreenBufferSize
		{
			get { return (CShellLayoutSizeConfigElement)this[ScreenBuffSizeName]; }
			set { this[ScreenBuffSizeName] = value; }
		}
	}

	public class CShellLayoutSizeConfigElement : ConfigurationElement
	{
		public const string WidthName = "width";
		public const string HeightName = "height";

		[ConfigurationProperty(WidthName, IsRequired = true)]
		[IntegerValidator(MinValue = short.MinValue, MaxValue = short.MaxValue)]
		public short Width
		{
			get { return (short)this[WidthName]; }
			set { this[WidthName] = value; }
		}

		[ConfigurationProperty(HeightName, IsRequired = true)]
		[IntegerValidator(MinValue = short.MinValue, MaxValue = short.MaxValue)]
		public short Height
		{
			get { return (short)this[HeightName]; }
			set { this[HeightName] = value; }
		}
	}

}
