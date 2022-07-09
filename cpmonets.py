import random

class Literal:
	def __init__(self, variable: str, sign: bool):
		self.variable = variable
		self.sign = sign

	def __str__(self):
		return ("" if self.sign else "~") + self.variable

	def evaluate(self, assignment: dict)->bool:
		return self.sign == assignment[self.variable]

class Clause:
	def __init__(self, literals: list):
		self.literals = [Literal(t[0], t[1]) for t in literals]

	def __str__(self):
		return " v ".join([str(l) for l in self.literals])

	def eval(self, assignment: dict)->bool:
		return any([literal.eval(assignment) for literal in self.literals])
	
	def get_variables(self)->set:
		return {literal.variable for literal in self.literals}
		
def get_sets_union(ls: list)->set:
	"""
		get the union of all sets in 'ls'.
	"""
	result = set()
	for s in ls:
		result += s
	return result

class CNF:
	def __init__(self, clauses: list):
		self.clauses = [Clause(c) for c in clauses]
	
	def __str__(self):
		return "("+")^(".join([str(c) for c in self.clauses])+")"
	
	def eval(self, assignment: dict)->bool:
		return all([clause.eval(assignment) for clause in self.clauses])
	
	def get_variables(self)->set:
		return get_sets_union([clause.get_variables() for clause in self.clauses])
	
def testCNF():
	"""
		build CNF from "[[("a", True), ("b", True)], [("c", False), ("A", False)]]"
		then print the result
	"""
	c1 = [("a", True), ("b", True)]
	c2 = [("c", False), ("A", False)]
	print(Clause(c2))

	cnf = CNF([c1, c2])
	print(cnf)

def get_random_assignment(variables: set)->dict:
	"""
		get a random assignment for the variables in 'variables'.
	"""
	return {v: random.choice([True, False]) for v in variables}

def try_SAT(cnf: CNF, max_tries: int)->bool:
	"""
		try to solve the CNF 'cnf' using 'max_tries' tries.
		return True if the CNF is satisfiable, False otherwise.
	"""
	for i in range(max_tries):
		assignment = get_random_assignment(cnf.get_variables())
		if cnf.eval(assignment):
			return True
	return False

def random_CNF(n: int, max_clauses: int, max_literals: int)->CNF:
	"""
		get a random CNF with 'n' variables, 'max_clauses' clauses, and 'max_literals' literals.
	"""
	clauses = []
	for i in range(max_clauses):
		clauses.append([])
		for j in range(random.randint(1, max_literals)):
			clauses