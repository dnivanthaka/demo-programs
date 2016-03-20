#!/usr/bin/env python
#!/usr/bin/env python

class BinaryTree:
    def __init__(self, rootObj):
        self.key   = rootObj
        self.left  = None
        self.right = None

    def insertLeft(self, newNode):
        self.key = BinaryTree(newNode)
