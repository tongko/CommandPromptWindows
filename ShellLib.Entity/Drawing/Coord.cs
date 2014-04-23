
using System.Diagnostics;

namespace ShellLib.Drawing
{
	[DebuggerDisplay("{X: {X}, Y: {Y}}")]
	public struct CCoord
	{
		public static readonly CCoord Empty = new CCoord(0, 0);

		private short _x;
		private short _y;

		public CCoord(CSize sz)
		{
			_x = sz.Width;
			_y = sz.Height;
		}

		public CCoord(short x, short y)
		{
			_x = x;
			_y = y;
		}

		public CCoord(int dw)
		{
			_x = LoWord(dw);
			_y = HiWord(dw);
		}

		public short X { get { return _x; } set { _x = value; } }

		public short Y { get { return _y; } set { _y = value; } }

		public bool IsEmpty { get { return _x == 00 && _y == 0; } }

		public static CCoord Add(CCoord c, CSize sz)
		{
			return new CCoord((short)(c._x + sz.Width), (short)(c._y + sz.Height));
		}

		public static CCoord Subtract(CCoord c, CSize sz)
		{
			return new CCoord((short)(c._x - sz.Width), (short)(c._y - sz.Height));
		}

		public override bool Equals(object obj)
		{
			if (!(obj is CCoord))
				return false;
			var c = (CCoord)obj;

			return (c._x == _x && c._y == _y);
		}

		public override int GetHashCode()
		{
			return _x ^ _y;
		}

		public void Offset(CCoord c)
		{
			Offset(c._x, c._y);
		}

		public void Offset(short dx, short dy)
		{
			_x += dx;
			_y += dy;
		}

		public override string ToString()
		{
			return "{X=" + _x.ToString(System.Globalization.CultureInfo.CurrentCulture)
				   + ",Y=" + _y.ToString(System.Globalization.CultureInfo.CurrentCulture)
				   + "}";
		}

		public static CCoord operator +(CCoord c, CSize sz)
		{
			return Add(c, sz);
		}

		public static bool operator ==(CCoord left, CCoord right)
		{
			return (left._x == right._x && left._y == right._y);
		}

		public static explicit operator CSize(CCoord c)
		{
			return new CSize(c._x, c._y);
		}

		public static explicit operator int(CCoord c)
		{
			int result = c._y;
			result = (result << 16) & 0xFFFF;
			result += c._x;
			return result;
		}

		public static bool operator !=(CCoord left, CCoord right)
		{
			return !(left == right);
		}

		public static CCoord operator -(CCoord c, CSize sz)
		{
			return Subtract(c, sz);
		}

		private static short LoWord(int dw)
		{
			return ((short)(((uint)dw) & 0xffff));
		}

		private static short HiWord(int dw)
		{
			return ((short)((((uint)dw) >> 16) & 0xffff));
		}
	}
}