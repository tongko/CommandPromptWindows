using System;

namespace WorkplaceLib.RedBlackTree
{
	public interface IRedBlackNode
	{
		bool IsRed { get; set; }
	}

	public class Node<TKey, TValue> : IRedBlackNode, IComparable<Node<TKey, TValue>> where TKey : IComparable
	{
		#region Properties

		public Node<TKey, TValue>[] Nodes { get; set; }

		public bool IsRed { get; set; }

		public TKey Key { get; set; }

		public TValue Data { get; set; }

		#endregion


		#region Methods

		public int CompareTo(Node<TKey, TValue> other)
		{
			return ((IComparable)Key).CompareTo(other.Key);
		}

		public override bool Equals(object obj)
		{
			var node = obj as Node<TKey, TValue>;
			if (node == null) return false;
			return ((IComparable)Key).CompareTo(node.Key) == 0;
		}

		public override int GetHashCode()
		{
			return 1;
		}

		#endregion


		#region Operators override

		public static bool operator ==(Node<TKey, TValue> lhs, Node<TKey, TValue> rhs)
		{
			if (Equals(lhs, null)) return Equals(rhs, null);
			if (Equals(rhs, null)) return false;

			return lhs.IsRed == rhs.IsRed && ((IComparable)lhs.Key).CompareTo(rhs.Key) == 0;
		}

		public static bool operator !=(Node<TKey, TValue> lhs, Node<TKey, TValue> rhs)
		{
			return !(lhs == rhs);
		}

		public static bool operator >(Node<TKey, TValue> lhs, Node<TKey, TValue> rhs)
		{
			return (lhs.CompareTo(rhs) == 1);
		}

		public static bool operator <(Node<TKey, TValue> lhs, Node<TKey, TValue> rhs)
		{
			return (lhs.CompareTo(rhs) == -1);
		}

		public static bool operator >=(Node<TKey, TValue> lhs, Node<TKey, TValue> rhs)
		{
			return (lhs.CompareTo(rhs) >= 0);
		}

		public static bool operator <=(Node<TKey, TValue> lhs, Node<TKey, TValue> rhs)
		{
			return (lhs.CompareTo(rhs) <= 0);
		}

		#endregion


		#region IComparable<T> members

		int IComparable<Node<TKey, TValue>>.CompareTo(Node<TKey, TValue> other)
		{
			return CompareTo(other);
		}

		#endregion
	}
}
