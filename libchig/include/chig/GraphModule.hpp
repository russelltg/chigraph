/// \file chig/GraphModule.hpp
/// Defines the GraphModule class

#ifndef CHIG_GRAPH_MODULE_HPP
#define CHIG_GRAPH_MODULE_HPP

#pragma once

#include "chig/Context.hpp"
#include "chig/DataType.hpp"

#include <boost/bimap.hpp>

namespace chig {
/// Module that holds graph functions
struct GraphModule : public ChigModule {
	/// Construct a GraphModule
	/// \param cont The context
	/// \param fullName The full name of the module
	/// \param dependencies The dependencies
	GraphModule(Context& cont, std::string fullName, gsl::span<std::string> dependencies);

	// No copy or move -- pointer only
	GraphModule(const GraphModule&) = delete;
	GraphModule(GraphModule&&)      = delete;
	GraphModule& operator=(const GraphModule&) = delete;
	GraphModule& operator=(GraphModule&&) = delete;

	// ChigModule interface
	///////////////////////

	Result nodeTypeFromName(gsl::cstring_span<> name, const nlohmann::json& jsonData,
	                        std::unique_ptr<NodeType>* toFill) override;

	DataType      typeFromName(gsl::cstring_span<> /*name*/) override { return {}; }
	std::vector<std::string> nodeTypeNames() const override;  // TODO: implement

	std::vector<std::string> typeNames() const override { return {}; }  // TODO: implement
	Result generateModule(llvm::Module& module) override;

	/////////////////////

	/// Create the associations from line number and function in debug info
	/// \return A bimap of function to line number
	boost::bimap<unsigned, NodeInstance*> createLineNumberAssoc() const;

	/// Serialize to disk in the context
	/// \return The Result
	Result saveToDisk() const;

	/// Get the path to the source file
	/// It's not garunteed to exist, because it could have not been saved
	/// \return The path
	boost::filesystem::path sourceFilePath() const {
		return context().workspacePath() / "src" / (fullName() + ".chigmod");
	}
	
	/// \name Function Creation and Manipulation
	/// \{

	/// Create a new function if it does't already exist
	/// \param name The name of the new function
	/// \param dataIns The data inputs to the function
	/// \param dataOuts The data outputs to the function
	/// \param execIns The exec inputs to the function
	/// \param execOuts The exec outputs to the function
	/// \param toFill The new GraphFunction, optional
	/// \return True if a new function was created, false otherwise
	bool createFunction(gsl::cstring_span<> name,
	                    std::vector<std::pair<DataType, std::string>> dataIns,
	                    std::vector<std::pair<DataType, std::string>> dataOuts,
	                    std::vector<std::string> execIns, std::vector<std::string> execOuts,
	                    GraphFunction** toFill = nullptr);

	/// Remove a function from the module
	/// \param name The name of the function to remove
	/// \return True if there was a function matching name that was removed
	bool removeFunction(gsl::cstring_span<> name);

	/// Remove a function from the module
	/// \param func The function to remove
	void removeFunction(GraphFunction* func);

	/// Get a function from the name
	/// \param name The name to get
	/// \return The GraphFunction or nullptr if it doesn't exist
	GraphFunction* graphFuncFromName(gsl::cstring_span<> name) const;

	/// Get functions
	/// \return The functions
	const std::vector<std::unique_ptr<GraphFunction>>& functions() const { return mFunctions; }
	
	///\}
	
	/// \name Struct Creation and Manipulation
	/// \{
	
	/// Create a new struct in the module
	/// \param name The name of the struct
	/// \inserted True if the struct was new, optional
	/// \return The new struct
	GraphStruct* getOrCreateStruct(std::string name, bool* inserted = nullptr);
	
	/// Remove a struct from the module by name
	/// \param name The name of the struct to remove
	/// \return True if a struct was actually removed
	bool removeStruct(gsl::cstring_span<> name);
	
	/// Remove a struct from the module by pointer
	/// \param tyToDel Struct to delete, must be in this module
	void removeStruct(GraphStruct* tyToDel);
	
	/// \}

private:
	std::vector<std::unique_ptr<GraphFunction>> mFunctions;
};
}  // namespace chig

#endif  // CHIG_GRAPH_MODULE_HPP