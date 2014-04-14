using System;

namespace WorkplaceLib.RedBlackTree
{
	// http://www.eternallyconfuzzled.com/tuts/datastructures/jsw_tut_rbtree.aspx
	public class Tree<TKey, TValue> where TKey : IComparable
	{
		#region Properties

		public Node<TKey, TValue> Root { get; set; }

		#endregion

		#region Public Methods

		public void Insert(TKey key, TValue data)
		{
			Root = Insert(Root, key, data);
			Root.IsRed = false;
		}

		public void Remove(TKey key, TValue data)
		{
			var done = false;

			Root = Remove(Root, key, data, ref done);
			if (Root != null)
				Root.IsRed = false;
		}

		/// <summary>
		/// Walks over every node in the tree and performs certain tests on the node and its children. 
		/// 1. Test is to see if a red node has red children.
		/// 2. Test makes sure that the tree is a valid binary search tree.
		/// 3. Test counts the black nodes along a path and ensures that all paths have the same black height.
		/// 
		/// </summary>
		/// <param name="root"></param>
		/// <returns>Returns 0 if tree is an invalid red black tree. Otherwise return the black height of tree.</returns>
		public static int SelfAssert(Node<TKey, TValue> root)
		{
			if (root == null)
				return 1;

			var ln = root.Nodes[0];
			var rn = root.Nodes[1];

			/* Consecutive red links */
			if (IsRed(root))
			{
				if (IsRed(ln) || IsRed(rn))
				{
					//var guilt = IsRed(ln) ? ln : rn;
					//throw new RedViolationException<T>("Red violation.", root, guilt, guilt == ln);
					return 0;	//Red violation
				}
			}


			var lhs = SelfAssert(ln);
			var rhs = SelfAssert(rn);

			/* Invalid binary search tree */
			if ((ln != null && ln >= root)
				|| (rn != null && rn <= root))
			{
				//puts("Binary tree violation");
				return 0;
			}

			/* Black height mismatch */
			if (lhs != 0 && rhs != 0 && lhs != rhs)
			{
				//puts("Black violation");
				return 0;
			}

			/* Only count black links */
			if (lhs != 0 && rhs != 0)
				return IsRed(root) ? lhs : lhs + 1;

			return 0;
		}

		public bool GetValue(TKey key, out TValue value)
		{
			value = default(TValue);

			if (Root == null) return false;

			var tempNode = Root;

			while (true)
			{
				var dir = key.CompareTo(tempNode.Key);
				if (dir == 0)
				{
					value = tempNode.Data;
					return true;
				}

				dir = dir == 1 ? 1 : 0;
				tempNode = tempNode.Nodes[dir];
				if (tempNode == null)
					break;
			}

			return false;
		}

		#endregion

		#region Private Methods

		private static bool IsRed(IRedBlackNode root)
		{
			return root != null && root.IsRed;
		}

		private static Node<TKey, TValue> SingleRotation(Node<TKey, TValue> root, int dir)
		{
			var notDir = 1 - dir;
			var save = root.Nodes[notDir];

			root.Nodes[notDir] = save.Nodes[dir];
			save.Nodes[dir] = root;

			root.IsRed = true;
			save.IsRed = false;

			return save;
		}

		private static Node<TKey, TValue> DoubleRotation(Node<TKey, TValue> root, int dir)
		{
			var notDir = 1 - dir;
			root.Nodes[notDir] = SingleRotation(root.Nodes[notDir], notDir);
			return SingleRotation(root, dir);
		}

		private static Node<TKey, TValue> MakeNode(TKey key, TValue data)
		{
			var rn = new Node<TKey, TValue> { Key = key, Data = data, IsRed = true, Nodes = new Node<TKey, TValue>[] { null, null } };

			return rn;
		}

		private static Node<TKey, TValue> Insert(Node<TKey, TValue> root, TKey key, TValue data)
		{
			if (root == null)
				root = MakeNode(key, data);
			else
			{
				var cmp = key.CompareTo(root.Key);
				if (cmp == 0) return root;

				if (cmp < 1) cmp = 0;
				root.Nodes[cmp] = Insert(root.Nodes[cmp], key, data);

				var notCmp = 1 - cmp;
				if (IsRed(root.Nodes[cmp]))
				{
					if (IsRed(root.Nodes[notCmp]))
					{
						/* Case 1 */
						root.IsRed = true;
						root.Nodes[0].IsRed = false;
						root.Nodes[1].IsRed = false;
					}
					else
					{
						/* Cases 2 & 3 */
						if (IsRed(root.Nodes[cmp].Nodes[cmp]))
							root = SingleRotation(root, notCmp);
						else if (IsRed(root.Nodes[cmp].Nodes[notCmp]))
							root = DoubleRotation(root, notCmp);
					}
				}
			}

			return root;
		}

		private static Node<TKey, TValue> Remove(Node<TKey, TValue> root, TKey key, TValue data, ref bool done)
		{
			if (root == null)
				done = true;
			else
			{
				if (root.Key.CompareTo(key) == 0)
				{
					if (root.Nodes[0] == null || root.Nodes[1] == null)
					{
						var save = root.Nodes[root.Nodes[0] == null ? 0 : 1];

						//	Case 0
						if (IsRed(root))
							done = true;
						else if (IsRed(save))
						{
							save.IsRed = false;
							done = true;
						}

						return save;
					}

					var heir = root.Nodes[0];

					while (heir.Nodes[1] != null)
						heir = heir.Nodes[1];

					root.Key = key = heir.Key;
					root.Data = data = heir.Data;
				}

				var dir = key.CompareTo(root.Key);
				root.Nodes[dir] = Remove(root.Nodes[dir], key, data, ref done);

				if (!done)
					root = RemoveBalance(root, dir, ref done);
			}

			return root;
		}

		private static Node<TKey, TValue> RemoveBalance(Node<TKey, TValue> root, int dir, ref bool done)
		{
			var notDir = 1 - dir;
			var p = root;
			var s = root.Nodes[notDir];

			//	Case reduction, remove red sibling
			if (IsRed(s))
			{
				root = SingleRotation(root, dir);
				s = p.Nodes[notDir];
			}

			if (s != null)
			{
				//	Balance sibling case
				if (!IsRed(s.Nodes[0]) && !IsRed(s.Nodes[1]))
				{
					if (IsRed(p))
						done = true;
					p.IsRed = false;
					s.IsRed = true;
				}
				else
				{
					var save = p.IsRed;
					var newRoot = root == p;

					p = IsRed(s.Nodes[notDir]) ? SingleRotation(p, dir) : DoubleRotation(p, dir);

					p.IsRed = save;
					p.Nodes[0].IsRed = p.Nodes[1].IsRed = false;

					if (newRoot)
						root = p;
					else
						root.Nodes[dir] = p;

					done = true;
				}
			}
			//else if (s.Nodes[dir] != null)
			//{
			//	//	Red sibling case
			//	var r = s.Nodes[dir];

			//	if (!IsRed(r.Nodes[0]) && !IsRed(r.Nodes[1]))
			//	{
			//		p = SingleRotation(p, dir);
			//		p.Nodes[dir].Nodes[notDir].IsRed = true;
			//	}
			//	else
			//	{
			//		if (IsRed(r.Nodes[dir]))
			//			s.Nodes[dir] = SingleRotation(r, notDir);
			//		p = DoubleRotation(p, dir);
			//		p.Nodes[dir].IsRed = false;
			//		p.Nodes[notDir].IsRed = true;
			//	}

			//	p.IsRed = p.Nodes[dir].IsRed = false;
			//	done = true;
			//}

			return p;
		}

		#endregion
	}
}
