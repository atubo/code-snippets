#!/usr/bin/python

class SegmentTreeBU:
	def __init__(self, n, NodeClass):
		self.NodeClass = NodeClass
		self.leaves = [None for i in range(n)]
		self.root = self.build(0, n-1, None)
	def build(self, i, j, parent):
		node = self.NodeClass(i, j, parent)
		if i == j:
			self.leaves[i] = node
		else:
			middle = i + (j-i)/2
			node.left  = self.build(i, middle, node)
			node.right = self.build(middle+1, j, node)
		return node
	def propagateUp(self, node):
		node.update()
		if node.changed and node.parent != None:
			self.propagateUp(node.parent)
	def updateLeaf(self, i, data):
		node = self.leaves[i]
		node.updateData(data)
		if node.changed and node.parent != None:
			self.propagateUp(node.parent)
	def findSucc(self, i, cond):
		p = self.leaves[i]
		while not cond(p):
			while p.parent and p == p.parent.right:
				p = p.parent
			if p.parent == None:
				return None
			p = p.parent.right
		while p.i != p.j:
			if cond(p.left):
				p = p.left
			else:
				p = p.right
		return p.i

class Node:
	def __init__(self, i, j, parent):
		self.i = i
		self.j = j
		self.parent = parent
		self.left   = None
		self.right  = None
		self.occupied = False
	def update(self):
		assert self.left and self.right
		oldOccupied = self.occupied
		self.occupied = self.left.occupied and self.right.occupied
		self.changed = (self.occupied != oldOccupied)
	def updateData(self, data):
		assert not self.left and not self.right
		oldOccupied = self.occupied
		self.occupied = data
		self.changed = (self.occupied != oldOccupied)

if __name__ == '__main__':
	import unittest
	cond = lambda node: not node.occupied
	class SegmentTreeBUTest(unittest.TestCase):
		def test_add(self):
			tree = SegmentTreeBU(4, Node)
			
			tree.updateLeaf(0, True)
			x = tree.findSucc(0, cond)
			self.assertEquals(x, 1)
			
			tree.updateLeaf(1, True)
			x = tree.findSucc(0, cond)
			self.assertEquals(x, 2)
			
			tree.updateLeaf(2, True)
			x = tree.findSucc(0, cond)
			self.assertEquals(x, 3)
			
			tree.updateLeaf(3, True)
			x = tree.findSucc(0, cond)
			self.assertEquals(x, None)

			tree.updateLeaf(2, False)
			x = tree.findSucc(0, cond)
			self.assertEquals(x, 2)
	unittest.main()
