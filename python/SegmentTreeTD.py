#!/usr/bin/python
import math
import copy

class SegmentTreeTD:
	def __init__(self, A):
		self.N = len(A)
		mSize = 2 * 2 ** (int(math.log(self.N, 2))+1) + 1
		self.M = [None for i in xrange(mSize)]
		self.initialize(1, 0, self.N-1, A)
	def initialize(self, node, b, e, A):
		if b == e:
			self.M[node] = copy.copy(A[b])
		else:
			self.initialize(2*node, b, (b+e)//2, A)
			self.initialize(2*node+1, (b+e)//2+1, e, A)
			if self.M[2*node].val <= self.M[2*node+1].val:
				self.M[node] = copy.copy(self.M[2*node])
			else:
				self.M[node] = copy.copy(self.M[2*node+1])
	def queryRecur(self, node, b, e, i, j, visitor):
		if i > e or j < b:
			return None
		visitor.visit(self.M[node])
		if b >= i and e <= j:
			return visitor.evaluate(self.M[node])
		p1 = self.queryRecur(2*node, b, (b+e)//2, i, j, copy.copy(visitor))
		p2 = self.queryRecur(2*node+1, (b+e)//2+1, e, i, j, copy.copy(visitor))

		if p1 == None:
			return p2
		if p2 == None:
			return p1
		if p1 <= p2:
			return p1
		return p2
	def query(self, i, j):
		visitor = Visitor()
		return self.queryRecur(1, 0, self.N-1, i, j, visitor);

	def updateRecur(self, node, b, e, i, j, data):
		if i > e or j < b:
			return
		if b >= i and e <= j:
			self.M[node].updateNode(data)
			return
		self.updateRecur(2*node, b, (b+e)//2, i, j, data)
		self.updateRecur(2*node+1, (b+e)//2+1, e, i, j, data)
		self.M[node].update(self.M[2*node], self.M[2*node+1])
	def update(self, i, j, data):
		self.updateRecur(1, 0, self.N-1, i, j, data)

class Node:
	def __init__(self, val):
		self.delta  = 0
		self.val    = val
	def updateNode(self, data):
		self.delta += data
	def update(self, child1, child2):
		tmp1 = child1.delta + child1.val
		tmp2 = child2.delta + child2.val
		self.val = min(tmp1, tmp2)

class Visitor:
	def __init__(self):
		self.delta = 0
	def visit(self, node):
		self.delta += node.delta
	def evaluate(self, node):
		return self.delta + node.val

def printST(tree):
	for i in range(1, len(tree.M)):
		if tree.M[i]:
			print "####%d" % i
			print tree.M[i].delta, tree.M[i].val

if __name__ == '__main__':
	import unittest
	class SegmentTreeTDTest(unittest.TestCase):
		def test1(self):
			a = [Node(i) for i in range(1, 5)]
			tree = SegmentTreeTD(a)
			tree.update(3, 3, -1)
			tree.update(0, 0, -1)
			x = tree.query(0, 0)
			self.assertEquals(x, 0)
			x = tree.query(3, 3)
			self.assertEquals(x, 3)
			x = tree.query(0, 1)
			self.assertEquals(x, 0)
			x = tree.query(2, 3)
			self.assertEquals(x, 3)
		def test2(self):
			a = [Node(0) for i in range(3)]
			tree = SegmentTreeTD(a)
			tree.update(0, 0, -1)
			tree.update(0, 0, 1)
			for i in range(3):
				x = tree.query(i, i)
				self.assertEquals(x, 0)
		def test3(self):
			a = [Node(-2) for i in range(3)]
			tree = SegmentTreeTD(a)
			#printST(tree)
			tree.update(0, 2, 2)
			#printST(tree)
			tree.update(2, 2, -1)
			#printST(tree)
			x = tree.query(0, 2)
			self.assertEquals(x, -1)

	unittest.main()
