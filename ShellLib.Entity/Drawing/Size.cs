using System.Diagnostics;
using System.Globalization;

namespace ShellLib.Drawing
{
	[DebuggerDisplay("{Width: {Width}, Height: {Height}}")]
	public struct CSize
	{
		public static readonly CSize Empty = new CSize(0, 0);

		private short _w;
		private short _h;

		public CSize(CCoord c)
		{
			_w = c.X;
			_h = c.Y;
		}

		public CSize(short w, short h)
		{
			_w = w;
			_h = h;
		}

		public short Width { get { return _w; } set { _w = value; } }

		public short Height { get { return _h; } set { _h = value; } }

		public bool IsEmpty { get { return _w == 0 && _h == 0; } }

		public static CSize Add(CSize sz1, CSize sz2)
		{
			return new CSize((short)(sz1.Width + sz2.Width), (short)(sz1.Height + sz2.Height));
		}

		public override bool Equals(object obj)
		{
			if (!(obj is CSize))
				return false;

			var sz = (CSize)obj;

			return _w == sz._w && _h == sz._h;

		}

		public override int GetHashCode()
		{
			return _w ^ _h;
		}

		public static CSize Subtract(CSize sz1, CSize sz2)
		{
			return new CSize((short)(sz1.Width - sz2.Width), (short)(sz1.Height - sz2.Height));
		}

		public override string ToString()
		{
			return "{Width=" + Width.ToString(CultureInfo.CurrentCulture)
				   + ", Height=" + Height.ToString(CultureInfo.CurrentCulture) + "}";
		}

		public static explicit operator CCoord(CSize sz)
		{
			return new CCoord(sz._w, sz._h);
		}

		public static CSize operator +(CSize left, CSize right)
		{
			return Add(left, right);
		}

		public static bool operator ==(CSize left, CSize right)
		{
			return left._w == right._w && left._h == right._h;
		}

		public static bool operator !=(CSize left, CSize right)
		{
			return !(left == right);
		}

		public static CSize operator -(CSize left, CSize right)
		{
			return Subtract(left, right);
		}
	}
}