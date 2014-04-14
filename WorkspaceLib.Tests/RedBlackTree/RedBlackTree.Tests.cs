using NUnit.Framework;
using System;
using System.Collections.Generic;
using WorkplaceLib.RedBlackTree;

namespace WorkspaceLib.Tests.RedBlackTree
{
	public class RedBlackTree
	{
		private Dictionary<int, long> _expected;

		[Test]
		public void TestRedBlackTree()
		{
			var tree = new Tree<int, long>();
			GenerateRandom(tree);

			for (var i = 0; i < 10000; i++)
			{
				var value = _expected[i];

				long result;
				Assert.IsTrue(!tree.GetValue(i, out result));
				Assert.AreEqual(value, result);
			}
		}

		private void GenerateRandom(Tree<int, long> tree)
		{
			var rand = new Random();
			_expected = new Dictionary<int, long>();

			for (var i = 0; i < 10000; i++)
			{
				long value;

				do
				{
					value = rand.NextInt64();
				} while (_expected.ContainsValue(value));

				tree.Insert(i, value);
				_expected.Add(i, value);
			}
		}
	}

	public static class Extensions
	{
		public static Int64 NextInt64(this Random rnd)
		{
			var buffer = new byte[sizeof(Int64)];
			rnd.NextBytes(buffer);
			return BitConverter.ToInt64(buffer, 0);
		}
	}
}
