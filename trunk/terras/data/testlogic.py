# -*- coding: utf-8 -*-

import os, sys

CONFIG_FILE = "data/config.yaml"
NODE_FILE = "data/node.yaml"

print("Loading Terras data...")

import terras

print dir(terras)

n1 = terras.Node("hello")
n2 = terras.Node("world")

terras.setNode("hello")

x = 5
