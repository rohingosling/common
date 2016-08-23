//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Project:	    N/A
// Application: Neural Network Class
// Class:	    NeuralNetwork
// Version:	    1.0
// Date:	    2015
// Author:	    Rohin Gosling
//
// Description:
//
//   Neural network class.
//
//   Note:
//   - Ported from my Java version of this class.
//
// Terminology:
//
// - Unit
//   + Refers to a single neural unit.
//   + Other names used in literature include; neuron, perceptron, perceptron unit, or in the
//     context of vectors, an element.
//
// - Input and Output Vectors
//   Vectors who's elements represent individual unit values (perceptron values).
//
// - Weight Vector
//   A vector who's elements represent the weights of all input dendrites to a single
//   unit (perceptron, neuron, etc).
//
// - Layer Operations
//   Calculations that carry and transform the input vector into a layer, through the various
//   stages that lead to the output vector.
//   + Weight Function.
//   + Network Function, or Net Function.
//   + Transfer Function.
//
// - Weight Function
//   + Function used to compute the relationship between the input vector and the weight vector.
//   + This is most commonly performed by calculating the Hadamard Product of the input and weight
//     vectors.
//
// - Network Function (Net Function)
//   + The network function integrates all the inputs and bias values, into a single scalar value 
//     to be used as the input into the transfer function.
//   + This is typically performed by summing up all the results of the weight function and the bias
//     unit (neuron).
//
// - Activation Function
//   The activation function defines the transfer threshold behaviour of a perceptron unit (neuron).
//
// Apendix A - DLL Managment
//
//   Create a DLL:
//
//     1. Set target configuration type to DLL.
//        Properties\Configuration Properties\General\Configuration Type = “Dynamic Library (.dll)
//     
//     2. Add a namespace to the DLL class.
//     
//     3. Add export symbol to compiler command line.
//        e.g. For the export symbol, “CLASS_NAME_EXPORTS”, then;
//        Properties\Configuration Properties\C/C++\Command Line\Additional Options = “/D CLASS_NAME_EXPORTS”
//     
//     4. Add a #define to the DLL header file, for the export symbol.
//        e.g. For the export symbol, “CLASS_NAME_EXPORTS”, then;
//     
//        #ifdef CLASS_NAME_EXPORTS
//            #define CLASS_NAME_API __declspec ( dllexport ) 
//        #else
//            #define CLASS_NAME_API __declspec ( dllimport ) 
//        #endif
//     
//     5. Apply the export symbol modifier to either the entire class, or selected members.
//
//     6. Specify explicate STL template classes to export before class decleration, where required.
//        e.g. template class __declspec ( dllexport ) std::vector<string>;
//             or
//        e.g. template class CLASS_NAME_API std::vector<string>;
//
//
//   Reference a DLL (Test):
//   
//     1. Create a test application.
//   
//     2. Add a reference to the DLL.
//        Properties\Common Properties\Add New Reference
//   
//     3. Add the DLL’s header file directory to the project.
//        Properties\Configuration Properties\VC++ Directories
//   
//     4. Optional: Add “using namespace” to the consumer class, for neater referencing.
//   
//
//   Reference a DLL (Implicate Linking):
//   
//     1. Create DLL comsumer application.
//
//     2. Copy both the DLL's .dll and .lib files, in the output folder.
//
//     3. Copy the DLL's header file to the source code folder.
//   
//     4. Add a reference to the LIB file.
//        Properties\Configuration Properties\Linker\Input\Aditional Dependencies = file_name.lib 
//   
//     4. Optional: Add “using namespace” to the consumer class, for neater referencing.
//
//
//   Reference a DLL (Explicate Linking):
//
//     1. TODO:
//
//     2. TODO:
//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

// DLL managment.

#ifdef NEURAL_NETWORK_EXPORTS
	#define NEURAL_NETWORK_API __declspec ( dllexport ) 
#else
	#define NEURAL_NETWORK_API __declspec ( dllimport ) 
#endif

// Pre-compiler directives.

#define DEBUG_LEVEL	0

#define ACTIVATION_FUNCTION_LIST	\
	LINEAR,							\
	SGN,							\
	STEP,							\
	SIGMOID,						\
	TANH,							\
	CUBIC,							\
	PYTHAGORIAN,					\
	QUADRATIC,						\
	SOFT_MAX,						\
	SOFT_PLUS						

// Include files.

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Namespace
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

using namespace std;

namespace common
{
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Explicate DLL export decleratioons for STL types.
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Global declerations
	// Note:
	// - We declare the enum out here, so that the compiler is able to explicatly export template types that use it inside the class.
	// - We do all this, in order to suppress the compiler warning C4251.

	enum class alias_activation_function_list { ACTIVATION_FUNCTION_LIST };

	// Explicate template exports.
	// Note:
	// - We do this, in order to suppress the compiler warning C4251 for templace classes that need to be exported to a DLL..
	
	template class NEURAL_NETWORK_API basic_string < char, char_traits<char>,        allocator < char >                          >; 
	template class NEURAL_NETWORK_API vector       < vector < float >,               allocator < vector < float > >              >;
	template class NEURAL_NETWORK_API vector       < vector < vector < float > >,    allocator < vector < vector < float > > >   >;
	template class NEURAL_NETWORK_API vector       < vector < int >,                 allocator < vector < int > >                >;
	template class NEURAL_NETWORK_API vector       < alias_activation_function_list, allocator < alias_activation_function_list >      >;
	

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Class
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	class NEURAL_NETWORK_API NeuralNetwork
	{
		//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		// Data Types
		//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
	public:

		using activation_function_list = alias_activation_function_list;	// Activation function types. Note: Due to the Windows requirement to export template classes, we reference an alias, instead of the actual enum.
		using Byte                     = unsigned char;						// 8-bit byte value.
		using Time                     = unsigned long long;				// Time measurement.
		using Index                    = unsigned long long;				// Indexing and counting.
		using Error                    = float;								// Error measurement.
		using Ratio                    = float;								// Real representation of a ratio. Ratio = n/d
		using Data                     = float;								// Input and output data.
		using Weight                   = float;								// Weight and bias values.
		using Unit                     = vector < Weight >;					// Input weight vector for a single perceptron unit. Weight[0] is used for the unit bias weight.
		using Layer                    = vector < Unit >;					// Neural network layer, composed of a vector of perceptron unit weight vectors.
		using Network                  = vector < Layer >;					// Neural network, composed of a vector of neural network layers.                   
		using Architecture             = vector < Byte >;					// Layer architecture, expressed as an array of perceptron counts per layer. the input layer is indexed at 0. the output layer is indexed at N-1.
		using InputVector              = vector < Data >;					// Network input vector. 
		using OutputVector             = vector < Data >;					// Network output vector.
		using OutputVectorMap          = vector < OutputVector >;			// Map cached feed forward computation results to network layers. 
		using ErrorVector              = vector < Error >;					// Backpropagation error vector.
		using ErrorVectorMap           = vector < ErrorVector >;			// Map cached backpropagation error vectors to layers.
		using ActivationFunction       = activation_function_list;			// Activation function type enumerations.
		using ActivationFunctionMap    = vector < ActivationFunction >;		// Map activation functions to neural network layers.
		
   
		//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		// Constants
		//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	public:
    
		// Neural network constants.
    
		const ActivationFunction C_DEFAULT_HIDDEN_LAYER_ACTIVATION_FUNCTION = ActivationFunction::SIGMOID;
		const ActivationFunction C_DEFAULT_OUTPUT_LAYER_ACTIVATION_FUNCTION = ActivationFunction::LINEAR;
    
		// Backpropagation constants.
				
		const Weight C_DEFAULT_WEIGHT                 = 0.0f;			// DEfault weight to use for input weights and unit bias initialization.
		const Error  C_DEFAULT_TRAINING_MSE           = 0.95f;			// Minimum Mean Squared Error (MSE).
		const Index  C_DEFAULT_TRAINING_EPOCH_COUNT   = 100;			// Number of epochs to train.
		const Time   C_DEFAULT_TRAINING_TIME_OUT      = 1000*60*5;		// ms*s*m = m minutes.
		const Ratio  C_DEFAULT_TRAINING_TO_TEST_RATIO = 0.9f;			// Training to test ratio = training samples / test samples.
    
		// Reporting and analysis constants.
    
		const int    C_DEFAULT_STRING_INDENT          = 4;
		const int    C_DEFAULT_STRING_MARGIN          = 4;
  
		//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		// Functions
		//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	public:

		// Constructor/s and destructor.

		NeuralNetwork                             ();
		NeuralNetwork                             ( Architecture architecture );
		NeuralNetwork                             ( const NeuralNetwork& neural_network );		// Copy constructor.
		~NeuralNetwork                            ();

		// Operators.

		NeuralNetwork& operator = ( const NeuralNetwork& neural_network );
    
		// Initialization.
    
		void initialize_network                   ( Architecture architecture );
		void set_layer_weights                    ( Weight weight, Index layer_index ); 
		void set_network_weights                  ( Weight weight );
		void randomize_layer_weights              ( Weight min, Weight max, Index layer_index );
		void randomize_network_weights            ( Weight min, Weight max );
    
		// NeuralNetwork operation functions.
    
		OutputVector compute_layer                ( InputVector x, Index layer_index );
		OutputVector compute_network              ( InputVector x );    		
		void         back_propagate               ( InputVector input_vector, OutputVector output_vector, Error min_mse, Index epoch_count, Time time_out );     
		Data         compute_network_function     ( Data x );        // x = b + sum(w*x)
		Data         compute_activation_function  ( Data x );        // y = f(x)
    
		// Reporting and analysis functions.
    
		string to_string                          ();
		string layer_to_string                    ( Index layer_index );
		string unit_to_string                     ( Index layer_index, Index unit_index );
		string input_vector_to_string             ( InputVector input_vector );
		string output_vector_to_string            ();
		string output_vector_to_string            ( Index layer_index );
		string output_vector_map_to_string        ();
		string error_vector_to_string             ( Index layer_index );
		string error_vector_map_to_string         ();
		string network_info_to_string             ();
		string backpropagation_results_to_string  ();
    
		// File management function.
    								              
		int save_network_to_csv                   ( string file_name);
		int save_network_to_bin                   ( string file_name);
		int save_network_to_bin_fixed             ( string file_name, Byte bit_width, bool signed_data );	// bit_width = { 8 bit or 16 bit }
		int save_network_to_text                  ( string file_name);

		int load_network_from_csv                 ( string file_name);
		int load_network_from_bin                 ( string file_name);
		int load_network_from_bin_fixed           ( string file_name, Byte bit_width, bool signed_data );	// bit_width = { 8 bit or 16 bit }		
    
		// Debugging functions.
    
		string log_to_string                      (                   string label, string message, bool time_visible );
		string log_to_console                     (                   string label, string message, bool time_visible );
		int    log_to_file                        ( string file_name, string label, string message, bool time_visible );

		// Accessors and mutators.
    
		void set_hidden_layer_activation_function ( ActivationFunction activation_function );
		void set_output_layer_activation_function ( ActivationFunction activation_function );
    
		Unit  get_unit                            ( Index layer_index, Index unit_index );
		Layer get_layer                           ( Index layer_index );
    
		void set_unit                             ( Index layer_index, Index unit_index, Unit unit );
		void set_layer                            ( Index layer_index, Layer layer );
    
		//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		// Data
		//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
	public:

		// Object management.
    
		unsigned long         id;
		string                name;
		string                description;

		// Neural network data.
    
		Network               network;                              // The main neural network data structure. Network[layer_index].Layer[unit_index].Unit[Weight_index].Weight
		ActivationFunctionMap activation_function_map;              // A map of activation functions to be applied to each layer in the network.
		Error                 backpropagation_result_mse;           // The mean squired error resulting from the last backpropagation training cycle.
		Index                 backpropagation_result_epoch_count;   // The number of epochs executed during the last backpropagation training cycle.
		Time                  backpropagation_result_run_time;      // The running time for the last backpropagation training cycle.
		OutputVectorMap       output_vector_map;                    // Intermediate backpropagation computation results.
		ErrorVectorMap        error_vector_map;                     // Intermediate backpropagation computation results.
    
		// Reporting and analysis data.
    
		int                   string_indent;
		int                   string_margin;
	};
		
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


