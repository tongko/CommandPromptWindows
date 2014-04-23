using System;
using System.Diagnostics;
using System.Globalization;

namespace ShellLib.Drawing
{
	[DebuggerDisplay("{X: {X}, Y: {Y}, Width: {Width}, Height: {Height}}")]
	public struct CRectangle
	{
		public static readonly CRectangle Empty = new CRectangle(0, 0, 0, 0);
		private short _x;
		private short _y;
		private short _w;
		private short _h;

		public CRectangle(CCoord c, CSize sz)
			: this(c.X, c.Y, sz.Width, sz.Height)
		{
		}

		public CRectangle(short x, short y, short w, short h)
		{
			_x = x;
			_y = y;
			_w = w;
			_h = h;
		}

		public short Bottom { get { return (short)(_y + _h); } }
		public short Height { get { return _h; } set { _h = value; } }
		public bool IsEmpty { get { return _x == 0 && _y == 0 && _h == 0 && _w == 0; } }
		public short Left { get { return _x; } }
		public CCoord Location { get { return new CCoord(_x, _y); } set { _x = value.X; _y = value.Y; } }
		public short Right { get { return (short)(_x + _w); } }
		public CSize Size { get { return new CSize(_w, _h); } set { _w = value.Width; _h = value.Height; } }
		public short Top { get { return _y; } }
		public short Width { get { return _w; } set { _w = value; } }
		public short X { get { return _x; } set { _x = value; } }
		public short Y { get { return _y; } set { _y = value; } }


		public static bool operator ==(CRectangle left, CRectangle right)
		{
			return left._x == right._x && left._y == right._y && left._w == right._w && left._h == right._h;
		}

		public static bool operator !=(CRectangle left, CRectangle right)
		{
			return !(left == right);
		}

		public static CRectangle FromLTRB(short l, short t, short r, short b)
		{
			return new CRectangle(l, t, (short)(r - l), (short)(b - t));
		}

		public override bool Equals(object obj)
		{
			if (!(obj is CRectangle)) return false;

			var rect = (CRectangle)obj;
			return rect._x == _x && rect._y == _y && rect._w == _w && rect._h == _h;
		}

		public bool Contains(short x, short y)
		{
			return _x <= x && _x + _w > x && _y <= y && _y + _h > y;
		}

		public bool Contains(CCoord c)
		{
			return Contains(c.X, c.Y);
		}

		public bool Contains(CRectangle rect)
		{
			return _x <= rect._x && _x + _w >= rect.Right && _y <= rect._y
				&& _y + _h >= rect.Bottom;
		}

		public override int GetHashCode()
		{
			return _x ^ (_y << 6 | (short)((ushort)_y >> 10))
				^ (_w << 13 | (short)((ushort)_w >> 3))
				^ (_h << 4 | (short)((ushort)_h >> 12));
		}

		public void Inflate(short dx, short dy)
		{
			_x -= dx;
			_y -= dy;
			_w += (short)(2 * dx);
			_h += (short)(2 * dy);
		}

		public void Inflate(CSize sz)
		{
			Inflate(sz.Width, sz.Height);
		}

		public static CRectangle Inflate(CRectangle rect, short dx, short dy)
		{
			var rectangle = rect;
			rectangle.Inflate(dx, dy);

			return rectangle;
		}

		public void Intersec(CRectangle rect)
		{
			var rectangle = Intersec(rect, this);
			_x = rectangle._x;
			_y = rectangle._y;
			_w = rectangle._w;
			_h = rectangle._h;
		}

		public static CRectangle Intersec(CRectangle a, CRectangle b)
		{
			var x = Math.Max(a.X, b.X);
			var w = Math.Min(a.Right, b.Right);
			var y = Math.Max(a.Y, b.Y);
			var h = Math.Min(a.Bottom, b.Bottom);

			return (w >= x && h >= y)
				? new CRectangle(x, y, (short)(w - x), (short)(h - y))
				: Empty;
		}

		public bool IntersecWith(CRectangle rect)
		{
			return rect._x < Right && _x < rect.Right && rect._y < Bottom && _y < rect.Bottom;
		}

		public static CRectangle Union(CRectangle a, CRectangle b)
		{
			var x = Math.Min(a.X, b.X);
			var w = Math.Max(a.Right, b.Right);
			var y = Math.Min(a.Y, b.Y);
			var h = Math.Max(a.Bottom, b.Bottom);
			return new CRectangle(x, y, (short)(w - x), (short)(h - y));
		}

		public void Offset(CCoord c)
		{
			Offset(c.X, c.Y);
		}

		public void Offset(short dx, short dy)
		{
			_x += dx;
			_y += dy;
		}

		public override string ToString()
		{
			return "{X="
				   + _x.ToString(CultureInfo.CurrentCulture)
				   + ",Y=" + _y.ToString(CultureInfo.CurrentCulture)
				   + ",Width=" + _w.ToString(CultureInfo.CurrentCulture)
				   + ",Height=" + _h.ToString(CultureInfo.CurrentCulture) + "}";
		}
	}
}