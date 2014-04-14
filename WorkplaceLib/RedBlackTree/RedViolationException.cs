//using System;

//namespace WorkplaceLib.RedBlackTree
//{
//	public class RedViolationException<T> : Exception where T : IComparable
//	{
//		#region Constructor

//		public RedViolationException()
//		{
//		}

//		public RedViolationException(string message, Node<T> parent, Node<T> guilt, bool isLeft)
//			: this(message, parent, guilt, isLeft, null)
//		{
//		}

//		public RedViolationException(string message, Node<T> parent, Node<T> guilt, bool isLeft, Exception innerException)
//			: base(message, innerException)
//		{
//			ParentNode = parent;
//			GuiltNode = guilt;
//			GuiltNodeIsLeft = isLeft;
//		}

//		#endregion


//		#region Properties

//		public Node<T> ParentNode { get; private set; }

//		public Node<T> GuiltNode { get; private set; }

//		public bool GuiltNodeIsLeft { get; private set; }

//		#endregion
//	}
//}
