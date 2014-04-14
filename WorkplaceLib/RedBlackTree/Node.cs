using System;

namespace WorkplaceLib.RedBlackTree
{
	public class Node<T> : IComparable<Node<T>> where T : IComparable
	{
		#region Properties

		public Node<T>[] Nodes;

		public bool IsRed;

		public T Data;

		#endregion


		#region Methods

		public int CompareTo(Node<T> other)
		{
			return ((IComparable)Data).CompareTo(other.Data);
		}

		public override bool Equals(object obj)
		{
			return ((IComparable)Data).CompareTo(obj) == 0;
		}

		public override int GetHashCode()
		{
			return 1;
		}

		#endregion


		#region Operators override

		public static bool operator ==(Node<T> lhs, Node<T> rhs)
		{
			if (lhs == null) return rhs == null;
			if (rhs == null) return false;

			return lhs.IsRed == rhs.IsRed && ((IComparable)lhs.Data).CompareTo(rhs.Data) == 0;
		}

		public static bool operator !=(Node<T> lhs, Node<T> rhs)
		{
			return !(lhs == rhs);
		}

		public static bool operator >(Node<T> lhs, Node<T> rhs)
		{
			return (lhs.CompareTo(rhs) == 1);
		}

		public static bool operator <(Node<T> lhs, Node<T> rhs)
		{
			return (lhs.CompareTo(rhs) == -1);
		}

		public static bool operator >=(Node<T> lhs, Node<T> rhs)
		{
			return (lhs.CompareTo(rhs) >= 0);
		}

		public static bool operator <=(Node<T> lhs, Node<T> rhs)
		{
			return (lhs.CompareTo(rhs) <= 0);
		}

		#endregion


		#region IComparable<T> members

		int IComparable<Node<T>>.CompareTo(Node<T> other)
		{
			return CompareTo(other);
		}

		#endregion
	}
}
