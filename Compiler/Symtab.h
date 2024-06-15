#pragma once

#include "Compiler/Exceptions.h"
#include "Compiler/Json.h"
#include "Compiler/Expr.h"
#include <string>
#include <map>
#include <set>
#include <vector>
#include <optional>


struct Symtab{
	Symtab();
	~Symtab();

	struct SymIntellisense {
		SymIntellisense(
			std::string symbol,
			Expr::ValueType type,
			int lineno
		);

		SymIntellisense(
			std::string symbol,
			Expr::ValueType type,
			int lineno,
			std::vector<std::string> arg_names
		);

		std::string toString() const;

		std::string symbol;
		int lineno;
		Expr::ValueType type;
		std::optional<std::vector<std::string>> arg_names;
	};

	/**
	 * @brief adds a new global-scope symbol to the table corresponding to a constant value.
	 * if symbol already in table @throw SymExistsException.
	 * @return the dsm expression that represents the new symbol.
	 */
	const std::string& defineGlobalValue(const std::string& sym, const SymIntellisense& isense);

	/**
	 * @brief adds a new global-scope symbol to the table corresponding to a function.
	 * also creates a new scope with all @param params as it's symbols.
	 * if symbol already in table @throw SymExistsException.
	 * @return the dsm expression of the new symbol.
	 */
	const std::string& defineFunction(const std::string& sym, const std::vector<std::string>& params, const SymIntellisense& isense);

	/**
	 * @brief closes top local-scope; all symbols within the scope will be undefined.
	 * If there are no local scopes left - @throw InternalError.
	 * the global scope cannot be closed.
	 */
	void closeScope();

	/**
	 * @brief get new unique symbol.
	 * the new symbol is anonymous meaning it cannot be referenced by the script code.
	 * anonymous symbols cannot be created by the script as they are impossible lexicographically.
	 * This does not define the new symbol.
	 * @return the newly created symbol.
	 */
	std::string getAnonSymbol();

	/**
	 * @brief define an anonymous function.
	 * @param sym should be the identifier returned by 'getAnonSymbol'.
	 * @param new_params the parameters added to the top scope by this new anon function.
	 * opens the local scope for the definition of this new function.
	 * if definition is not possible, @throw InternalError.
	 * @return the dsm exp of the new function.
	 */
	const std::string& defineAnonFunc(const std::string& sym, const std::vector<std::string>& new_params = {});

	/**
	 * @return all symbols from local scopes.
	 * the returned vector begining is the first symbols from the earliest scope,
	 * the last symbols in the returned vector are the last symbols from the latest scope.
	 */

	const std::vector<std::vector<std::string>>& getLocalScopes() const;
	
	/**
	 * @return a string containing all local parameters in format '(x, y, z ...)'
	 * The ordering is the same as in 'getLocalScopes'.
	 */
	std::string getLocalsInFormat(
			const std::map<std::string, std::string>& replace={}, 
			const std::set<std::string> ignore={}
	) const;

	std::vector<std::string> getVariables() const;

	std::string getVariablesFormat(
			const std::vector<std::string> variables,
			const std::map<std::string, std::string>& replace={}, 
			const std::set<std::string> ignore={}
	) const;

	struct SymInfo{
		SymInfo(const std::string& dsm_exp, Expr::ValueType type);
		virtual const std::string& getDsmExp() const;
		virtual Expr::ValueType getType() const;
		
		std::optional<SymIntellisense> isense;
	private:
		std::string dsm_exp;
		Expr::ValueType type;
	};

	/**
	 * @brief returns information associated with @param sym.
	 * if @param sym is not in the table - @throw NoSuchSymException.
	 */
	const SymInfo& getSymInfo(const std::string& sym) const;

	struct SymExistsException : SemanticError{
		SymExistsException(const std::string& sym);
		virtual std::string errorMsg() const override;
	private:
		const std::string& sym;
	};
	struct NoSuchSymException : SemanticError{
		NoSuchSymException(const std::string& sym);
		virtual std::string errorMsg() const override;
	private:	
		const std::string& sym;
	};
	
	void openScope(const std::vector<std::string>& local_symbols);
	void reset();

	std::string generateIntellisense() const;
	
private:
	std::map<std::string, SymInfo*> table;
	std::vector<std::vector<std::string>> nested_scopes;
	int anon_count;

	void defineBuiltInSymbols();
	void checkDefinable(const std::string& sym);
	SymInfo* allocateSubscriptSymInfo(const std::string& sym);
};
