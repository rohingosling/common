//--------------------------------------------------------------------------------------------------
// Project:	    N/A
// Application: All AI and Machine Learning applications.
// Class:	    MathML
// Version:	    1.0
// Date:	    2015
// Author:	    Rohin Gosling
//
// Description:
//
//   Static math functions for use in AI and machine learning applications.
//
//--------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "math_ml.h"

#define ASSEMBLER		__asm
#define ASSEMBLER_BEGIN	__asm {
#define ASSEMBLER_END	}

using namespace common;

namespace common
{
	//--------------------------------------------------------------------------------------------------
	// Constructor 1/1
	//--------------------------------------------------------------------------------------------------

	MathML::MathML ( void )
	{
	}

	//--------------------------------------------------------------------------------------------------
	// Destructor
	//--------------------------------------------------------------------------------------------------

	MathML::~MathML ( void )
	{
	}

	//--------------------------------------------------------------------------------------------------
	// Fast square root.	
	//--------------------------------------------------------------------------------------------------

	inline double MathML::fast_sqrt ( double x )
	{
		ASSEMBLER_BEGIN

			FLD		x		/* Load the first argument onto the stack                                            */
			FSQRT			/* Replace the value at location 0 on the stack, with the square root of it's value. */

		ASSEMBLER_END
	}

	//--------------------------------------------------------------------------------------------------
	// Fast e^x
	//--------------------------------------------------------------------------------------------------

	inline double MathML::fast_exp ( double x )
	{
		ASSEMBLER_BEGIN

			/* TODO: */

		ASSEMBLER_END

		return 0.0;
	}

	//--------------------------------------------------------------------------------------------------
	// Sigmoid activation function.
	//
	//                 1
	//           ────────────
	//  f(x)  =  ┌       -x ┐
	//           │  1 + e   │
	//           └          ┘ 
	//
	//--------------------------------------------------------------------------------------------------

	double MathML::sigmoid ( double x )
	{
		// Compute the sigmoid function.

		double ex = exp ( -x );             // Raise e to the power of -x. 
		double y  = 1 / ( 1 + ex );         // Calculate the sigmoid function.

		// Return the result.

		return y;
	}

	//--------------------------------------------------------------------------------------------------
	// Parameterized sigmoid activation function.
	//
	//                  1
	//           ──────────────
	//  f(x)  =  ┌       -k·x ┐
	//           │  1 + e     │
	//           └            ┘  
	//
	//--------------------------------------------------------------------------------------------------

	double MathML::sigmoid ( double x, double k )
	{
		// Compute the parameterized sigmoid function.

		double t  = -k*x;                   // Exponent.           
		double ex = exp ( t );              // Raise e to the power of t. 
		double y  = 1 / ( 1 + ex );         // Calculate the sigmoid function.

		// Return the result.

		return y;
	}

	//--------------------------------------------------------------------------------------------------
	// Derivative of a sigmoid function.
	//
	//                          x
	//                         e
	//            dy     ─────────────
	//  f'(x)  =  ──  =  ┌   x      ┐2
	//            dx     │  e  + 1  │
	//                   └          ┘  
	//
	//--------------------------------------------------------------------------------------------------

	double MathML::dydx_sigmoid ( double x )
	{
		// Initialize local variables.

		double dy   = 0.0;
		double dx   = 0.0;
		double dydx = 0.0;

		// Compute the derivitive of the sigmoid function.

		dy   = exp ( x );
		dx   = ( dy + 1 );
		dydx = dy / dx*dx;            // Calculate the derivative of the sigmoid function.

		// Return the result.

		return dydx;
	}

	//--------------------------------------------------------------------------------------------------
	// Derivative of a parameterizd sigmoid function.
	//
	//                          kx
	//                       k·e
	//            dy     ─────────────
	//  f'(x)  =  ──  =  ┌   kx      ┐2
	//            dx     │  e   + 1  │
	//                   └           ┘  
	//
	//--------------------------------------------------------------------------------------------------

	double MathML::dydx_sigmoid ( double x, double k )
	{
		// Compute the derivitive of the sigmoid function.

		double dy   = k*exp ( k*x );
		double dx   = ( dy + 1 );
		double dydx = dy / dx*dx;            // Calculate the derivative of the sigmoid function.

		// Return the result.

		return dydx;
	}



	//--------------------------------------------------------------------------------------------------
	// Sign function.
	//                  ┌   
	//                  │ -1 if x < 0
	//  y = sgn ( x ) = ┤  0 if x = 0
	//                  │  1 if x > 0
	//                  └
	//--------------------------------------------------------------------------------------------------

	double MathML::sgn ( double x )
	{
		// Declare local varaibles.

		double y = 0.0;

		// Compute the sign function.

		     if ( x <  0.0 ) y = -1.0;		     
		else if ( x == 0.0 ) y =  0.0;
		else if ( x >  0.0 ) y =  1.0;

		// Return the result.

		return y;
	}

	//--------------------------------------------------------------------------------------------------
	// Step function.
	//                 ┌   
	//                 │ 0 if x < 0
	//  y = step (x) = ┤
	//                 │ 1 if x ≥ 0
	//                 └
	//--------------------------------------------------------------------------------------------------

	double MathML::step ( double x )
	{
		// Declare local varaibles.

		double y = 0.0;

		// Compute the sign function.

		if ( x <  0.0 ) y =  0.0;
		if ( x >= 0.0 ) y =  1.0;

		// Return the result.

		return y;
	}

	//--------------------------------------------------------------------------------------------------
	// Rectified Linear Unit.
	//                      ┌   
	//                      │ 0 if x < 0
	//  y = ReLU ( x, 0 ) = ┤
	//                      │ x if x ≥ 0
	//                      └
	//--------------------------------------------------------------------------------------------------

	double MathML::relu ( double x )
	{
		// Declare local varaibles.

		double y = 0.0;

		// Compute Rectifying linear unit function (ReLU).
		
		if ( x >= 0.0 ) y = x;
		if ( x <  0.0 ) y = 0.0;

		// Return the result.

		return y;
	}

	//--------------------------------------------------------------------------------------------------
	// Deribative of Rectified Linear Unit.
	//                                  ┌   
	//          dy					    │ 0 if x < 0
	//  f'(x) = ── = ReLU' ( x, 0 ) = = ┤
	//          dx					    │ 1 if x ≥ 0
	//                                  └  
	//----------------------------------------------------------------------------------------------------

	double MathML::dydx_relu ( double x )
	{
		// Declare local varaibles.

		double dydx = 0.0;

		// Compute Rectifying linear unit function (ReLU).
		
		if ( x >= 0.0 ) dydx = 1;
		if ( x <  0.0 ) dydx = 0.0;

		// Return the derivitive.

		return dydx;
	}
	
	//--------------------------------------------------------------------------------------------------
	// Parameterized Linear Rectified Unit.
	//                      ┌   
	//                      │ k·x if x < 0
	//  y = ReLU ( x, k ) = ┤
	//                      │   x if x ≥ 0
	//                      └
	//--------------------------------------------------------------------------------------------------

	double MathML::prelu ( double x, double k )
	{
		// Declare local varaibles.

		double y = 0.0;

		// Compute Rectifying linear unit function (ReLU).
		
		if ( x >= 0.0 ) y = x;
		if ( x <  0.0 ) y = k*x;

		// Return the result.

		return y;
	}

	//--------------------------------------------------------------------------------------------------
	// Derivative of parameterized Linear Rectified Unit.
	//                                  ┌   
	//          dy					    │ k if x < 0
	//  f'(x) = ── = ReLU' ( x, k ) = = ┤
	//          dx					    │ 1 if x ≥ 0
	//                                  └  
	//----------------------------------------------------------------------------------------------------

	double MathML::dydx_prelu ( double x, double k )
	{
		// Declare local varaibles.

		double dydx = 0.0;

		// Compute Rectifying linear unit function (ReLU).
		
		if ( x >= 0.0 ) dydx = 1;
		if ( x <  0.0 ) dydx = k;

		// Return the derivitive.

		return dydx;
	}

	//--------------------------------------------------------------------------------------------------
	//                   
	//  f(x) = ln ( 1 + e^x )
	//
	//--------------------------------------------------------------------------------------------------
	
	double MathML::softplus ( double x )
	{
		// Compute the parameterized sigmoid function.

		double t = 1 + exp ( x );		// Natural logarythmic parameter..           		
		double y = log ( t );			// Calculate softplus(x).

		// Return the result.

		return y;
	}

	//--------------------------------------------------------------------------------------------------
	//
	//            ┌      (kx+a) ┐
	//  f(x) = ln │ 1 + e       │
	//            └             ┘
	//
	//--------------------------------------------------------------------------------------------------
	
	double MathML::softplus ( double x, double k, double a )
	{
		// Compute the parameterized sigmoid function.

		double t = 1 + exp ( k*x - a );		// Natural logarythmic parameter..           		
		double y = log ( t );				// Calculate softplus(x).

		// Return the result.

		return y;
	}

	//--------------------------------------------------------------------------------------------------
	//                  x 
	//          dy     e
	//  f'(x) = ── = ──────
	//          dx        x 
	//               1 + e
	//--------------------------------------------------------------------------------------------------
	
	double MathML::dydx_softplus ( double x )
	{
		// Compute the derivitive of the sigmoid function.

		double t    = exp ( x );		
		double dx   = 1 + t;
		double dydx = t / dx;            // Calculate the derivative of the softplus function.

		// Return the result.

		return dydx;
	}

	//--------------------------------------------------------------------------------------------------
	//                      (kx+a) 
	//          dy       k·e
	//  f'(x) = ── = ──────────────
	//          dx           (kx+a) 
	//                1 + k·e
	//--------------------------------------------------------------------------------------------------
	
	double MathML::dydx_softplus ( double x, double k, double a )
	{
		// Compute the derivitive of the sigmoid function.

		double dy   = k*exp ( k*x - a );		
		double dx   = 1 + dy;
		double dydx = dy / dx;            // Calculate the derivative of the paramaterized softplus function.

		// Return the result.

		return dydx;
	}

	//--------------------------------------------------------------------------------------------------
	//
	//            ┌      (kx-a) ┐
	//  f(x) = ln │ 1 + e       │, where, a = k - ln ( e - 1 )
	//            └             ┘
	//
	//--------------------------------------------------------------------------------------------------
	
	double MathML::softplus_normal ( double x, double k )
	{
		const double e = 2.71828182;						// Euler's number"

		// Calculate normalization factor.

		double a = k - log ( e - 1 );

		// Compute the normaliozed softplus function.

		double t = 1 + exp ( k*x - a );		// Natural logarythmic parameter..           		
		double y = log ( t );				// Calculate softplus(x).

		// Return the result.

		return y;
	}

	//--------------------------------------------------------------------------------------------------
	//                      (kx+a) 
	//          dy       k·e
	//  f'(x) = ── = ──────────────	, where, a = k - ln ( e - 1 )
	//          dx           (kx+a) 
	//                1 + k·e
	//--------------------------------------------------------------------------------------------------
	
	double MathML::dydx_softplus_normal ( double x, double k )
	{
		const double e = 2.71828182;						// Euler's number"

		// Calculate normalization factor.

		double a = k - log ( e - 1 );

		// Compute the derivitive of the sigmoid function.

		double dy   = k*exp ( k*x - a );		
		double dx   = 1 + dy;
		double dydx = dy / dx;            // Calculate the derivative of the paramaterized softplus function.

		// Return the result.

		return dydx;
	}

	//--------------------------------------------------------------------------------------------------
	// Normalized Softsign activation function.
	// 
	// Function:
	//
	//           2·x
	//   f(x) = ─────
	//          1+|x|
	//                                                                      ┌       ┐
	// Notes:                                                               │ π     │
	// - Normalized Softsign, is similar to normalized arc tangent, y = atan│ ─ · x │, in the range -1 ≤ x ≤ 1.
	//                                                                      │ 2     │
	//                                                                      └       ┘
	//--------------------------------------------------------------------------------------------------
	
	double MathML::softsign ( double x )
	{
		// Compute absolute value of x.
		// We do it implicatly here, rather than through a call to abs(x), for the sake of maximizing perfromance.

		double xa = ( x < 0 ) ? -x : x;

		// Compute soft sign function.
		
		double y = 2*x / ( 1 + xa );

		// Return the result.

		return y;
	}

	//--------------------------------------------------------------------------------------------------
	// Derivative of the Softsign activation function.
	//
	// Function:
	//
	//              2
	//   f'(x) = ────────
	//           (1+|x|)²
	//
	//--------------------------------------------------------------------------------------------------
	
	double MathML::dydx_softsign ( double x )
	{
		// Compute absolute value of x.
		// We do it implicatly here, rather than through a call to abs(x), for the sake of maximizing perfromance.

		double xa = ( x < 0 ) ? -x : x;

		// Compute soft sign function.
		
		double dy   = ( 1 + xa );
		double dydx = 2/dy*dy;

		// Return the result.

		return dydx;
	}

	//--------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------

	double MathML::parabolic ( double x )
	{
		// Declare local variables.
		
		double y  = 0.0;
		double a  = 0.0;

		// Compute parabolic activation function.

		if ( x >= -1.0 )
		{
			a = ( x + 1 );
			y = a*a/2 - 1;
		}
		else
		{
			y = -1.0;
		}
		

		// Return the result.

		return y;
	}

	//--------------------------------------------------------------------------------------------------
	// Note: Check derivative.
	//--------------------------------------------------------------------------------------------------

	double MathML::dydx_parabolic ( double x )
	{
		// Declare local variables.
		
		double dydx  = 0.0;		

		// Compute parabolic activation function.

		if ( x >= -1.0 )
		{	
			dydx = x + 1;
		}
		else
		{
			dydx = 0.0;
		}
		

		// Return the result.

		return dydx;
	}

	//--------------------------------------------------------------------------------------------------	
	// Bipolar quadratic activation function
	//
	// - Operation Count:
	//   - Multiplicative: 1 x 2 = 2
	//   - Additive:       2 x 2 = 4
	//   - Total:          3 x 2 = 6
	//                   
	//      ┌   
	//      │ (x+1)²-1 if x < 0
	//  y = ┤
	//      │ 1-(x-1)² if x ≥ 0
	//      └
	//
	// Factorized form, for faster computation. 33.3% faster.
	//
	// - Operation Count:
	//   - Multiplicative: 1 x 2 = 2
	//   - Additive:       1 x 2 = 2
	//   - Total:          2 x 2 = 4
	//
	//      ┌   
	//      │  x(x+2) if x < 0
	//  y = ┤
	//      │ -x(x-2) if x ≥ 0
	//      └
	//
	//--------------------------------------------------------------------------------------------------

	double MathML::quadratic ( double x )
	{
		// Declare local variables.
		
		double y  = 0.0;		

		// Compute bipolar quadratic activation function.

	    if      ( x <= -1.0 ) y = -1.0;
		else if ( x >=  1.0 ) y =  1.0;
		else
		{
			if ( x <  0 ) y =  x*(x+2);
			if ( x >= 0 ) y = -x*(x-2);
		}

		// Return the result.

		return y;
	}

	//--------------------------------------------------------------------------------------------------	
	// Derivative of bipolar quadratic activation function
	//                   
	//       ┌   
	//       │ 2(x+1) if x < 0
	//  y' = ┤
	//       │ 2(x-1) if x ≥ 0
	//       └
	//      	
	//--------------------------------------------------------------------------------------------------

	double MathML::dydx_quadratic ( double x )
	{
		// Initialize local variables.
		
		double dydx = 0.0;

		// Compute the derivitive.
		
		if      ( x <= -1.0 ) dydx = 0.0;		// Clamp to min gradient.
		else if ( x >=  1.0 ) dydx = 0.0;		// Clamp to max gradient.
		else
		{
			if ( x <  0 ) dydx = 2*(x+1);		// Compute negative quadratic function segment.
			if ( x >= 0 ) dydx = 2*(x-1);		// Compute positive quadratic function segment.
		}		

		// Return the result.

		return dydx;
	}
	
	//--------------------------------------------------------------------------------------------------	
	// Normalized cubic polynomial activation function.	
	//
	// Function:
	//                   
	//             3x - x³
	//   f(x)  =  ────────
	//                2
	//          	
	// General cubic polynoimial:
	//                               
	//   Cubic Polynomial:    y  =  a + bx + cx² + dx³
	//                                            
	//   Derivative:          y' =  bx + 2cx + 3dx²
	// 
	// Neural network activation function, equation system:
	// 
	//   Equation 0:      f(-1)  = -1  =  a - b + c - d    ...Output -1 if x = -1.
	//   Equation 1:      f( 1)  =  1  =  a + b + c + d    ...Output  1 if x =  1.
	//   Equation 2:     f'(-1)  =  0  = -b - 2c + 3d      ...Gradient is 0 at -1.
	//   Equation 3:     f'( 1)  =  0  =  b + 2c + 3d      .. Gradient is 0 at  1.
	// 
	// Coeficient solution:
	//
	//   a =  0
	//   b =  3/2
	//   c =  0
	//   d = -1/2
	//
	// Notes:
	//
	// - Cubic polinimoal is similar to Sinusoid, y = sin(πx/2).
	//
	//--------------------------------------------------------------------------------------------------

	double MathML::cubic ( double x )
	{
		// Initialize local variables.

		double y = 0.0;
	
		// Compute cubic activation function.

		if      ( x <= -1.0 ) y = -1.0;		// Clamp to min.
		else if ( x >=  1.0 ) y =  1.0;		// Clamp to ax.
		else
		{
			y = ( 3*x - x*x*x ) / 2;		// Compute cubic polynomial.
		}
	
		// Return the result.

		return y;
	}

	//--------------------------------------------------------------------------------------------------	
	// Derivative of cubic polynomial activation function.
	//                   
	//              3x - x³
	//    f(x) =   ────────
	//                 2
	//          	                    
	//             3(x² - 1)
	//   f'(x) = - ─────────
	//                 2
	//         	
	//--------------------------------------------------------------------------------------------------

	double MathML::dydx_cubic ( double x )
	{
		// Initialize local variables.
		
		double dydx = 0.0;		

		// Compute the derivitive of the cubic activation function.

		if      ( x <= -1.0 ) dydx = 0.0;	// Clamp to min gradient.
		else if ( x >=  1.0 ) dydx = 0.0;	// Clamp to max gradient.
		else
		{
			dydx = -3*( x*x - 1 ) / 2;		// Comute cubic derivative.
		}
		
		// Return the result.

		return dydx;
	}

	//--------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------

	double MathML::pythagorean ( double x )
	{
		// Initialize local variables.

		double y = 0.0;

		// Compute activation function.

		if      ( x <= -1.0 ) y = -1.0;				// Clamp to min.
		else if ( x >=  1.0 ) y =  1.0;				// Clamp to max.
		else
		{
			if ( x <  0 ) y = -sqrt(-x*(x+2));		// Compute negative function segment.
			if ( x >= 0 ) y =  sqrt(-x*(x-2));		// Compute positive function segment.
		}

		// Return the result.

		return y;
	}

	//--------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------

	double MathML::dydx_pythagorean ( double x )
	{
		// Initialize local variables.

		double dydx = 0.0;
		double dx   = 0.0;
		double dy   = 0.0;

		// Compute derivative.

		if      ( x <= -1.0 ) dydx = -1.0;			// Clamp to min gradient.
		else if ( x >=  1.0 ) dydx =  1.0;			// Clamp to max gradient.
		else
		{
			if ( x <  0 )
			{
				dy   = 1 + x;
				dx   = sqrt ( -x*( x + 2 ) );				
				dydx = dy/dx;						// Compute negative function segment.
			}
			if ( x >= 0 )
			{
				dy   = 1 - x;
				dx   = sqrt ( -x*( x - 2 ) );				
				dydx = dy/dx;						// Compute positive function segment.
			}
		}

		// Return the result.

		return dydx;
	}

	//--------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------

	double MathML::quadratic_transpose ( double x )
	{
		// Initialize local variables.

		double y = 0.0;

		// Compute activation function.

		if      ( x <= -1.0 ) y = -1.0;			// Clamp to min.
		else if ( x >=  1.0 ) y =  1.0;			// Clamp to max.
		else
		{
			if ( x <  0 ) y = -sqrt ( -x );		// Compute negative function segment.
			if ( x >= 0 ) y =  sqrt (  x );		// Compute positive function segment.
		}

		// Return the result.

		return y;
	}

	//--------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------

	double MathML::dydx_quadratic_transpose ( double x )
	{
		// Initialize local variables.

		double dydx = 0.0;
		double dx   = 0.0;		

		// Compute derivative.

		if      ( x <= -1.0 ) dydx = -1.0;		// Clamp to min gradient.
		else if ( x >=  1.0 ) dydx =  1.0;		// Clamp to max gradient.
		else
		{
			if ( x <  0 )
			{	
				dx   = 2*sqrt ( -x );				
				dydx = 1/dx;					// Compute negative function segment.
			}
			if ( x >= 0 )
			{
				dx   = 2*sqrt ( x );				
				dydx = 1/dx;					// Compute positive function segment.
			}
		}

		// Return the result.

		return dydx;
	}

	//--------------------------------------------------------------------------------------------------	
	// Normalized hyperbolic tangent.
	//                   
	//   f(x) = coth(π)·tanh(π·x)
	//     
	//                 sinh(2π)
	//   coth(π) = - ────────────
	//               1 - cosh(2π)
	//
	//--------------------------------------------------------------------------------------------------

	double MathML::tanh_normal ( double x )
	{
		// Local constants.
				
		const double π  = 3.1415926535897932;
		const double π2 = 2*π;

		// Initialze local variables.

		double y = 0.0;
		
		// Compute substitutions for coth(π) computation.

		double dyu  = sinh ( π2 );			// coth numerator.
		double dxu  = 1-cosh ( π2 );		// coth denominator.
		double coth = -dyu/dxu;				// Compute coth(π)

		// Compute normalized hyperbolic tangent.

		y = coth*tanh ( π*x );

		// Return the result.

		return y;
	}

	//--------------------------------------------------------------------------------------------------	
	// Parameterized normalized hyperbolic tangent.
	//                   
	//   f(x) = coth(k·π)·tanh(k·π·x)
	//     
	//                   sinh(2·k·π)
	//   coth(k·π) = - ───────────────
	//                 1 - cosh(2·k·π)
	//       	
	//--------------------------------------------------------------------------------------------------

	double MathML::tanh_normal ( double x, double k )
	{
		// Local constants.
				
		const double π  = 3.1415926535897932;
		const double π2 = 2*π;

		// Initialiuze local variables.

		double y = 0.0;		

		// Compute substitutions for coth(k·π) computation.

		double kπ2  = k*π2;				// k multiplied by 360 degrees in radians.
		double dyu  = sinh (kπ2);		// coth numerator.
		double dxu  = 1-cosh (kπ2);		// coth denominator.
		double coth = -dyu/dxu;			// Compute coth(k·π)

		// Compute parameterized normalized hyperbolic tanget.

		y = coth*tanh (k*π*x);			// Compute activation function.

		// Return the result.

		return y;
	}

	//--------------------------------------------------------------------------------------------------	
	// Deerivative of normalized hyperbolic tangent.
	//                   
	//   f(x) = coth(π)·tanh(π·x)
	//
	//	f'(x) = π·coth(π)·sech²(π·x)
	//
	//--------------------------------------------------------------------------------------------------

	double MathML::dydx_tanh_normal ( double x )
	{
		// Local constants.

		const double π  = 3.1415926535897932;
		const double π2 = 2*π;

		// Initialize local variables.

		double dydx = 0.0;		

		// Compute substitutions for coth(π) and sech²(π·x) computation.

		double dyu   = sinh (π2);		// coth numerator.
		double dxu   = 1-cosh (π2);		// coth denominator.
		double coth  = -dyu/dxu;		// Compute coth(2·π) 
		double sech  = 1/cosh (π*x);	// Compute hyperbolic secant.		
		double sech2 = sech*sech;		// Compute the square of the hyperbolic secant, sech²(π·x).

		// Compute normalized hyperbolic tangent.

		dydx = π*coth*sech2;			// Compute derivitive.

		// Return the result.

		return dydx;
	}

	//--------------------------------------------------------------------------------------------------	
	// Normalized sinusoid.
	//                   
	//             ┌       ┐
	//             │ π     │
	//  f(x) = sin │ ─ · x │
	//             │ 2     │
	//             └       ┘
	//   	
	//--------------------------------------------------------------------------------------------------

	double MathML::sin_normal ( double x )
	{
		// Local constants.

		const double π   = 3.1415926535897932;
		const double π÷2 = π/2; 

		// Initialize local variables.

		double y = 0.0;
		
		// Compute parameterized normalized hyperbolic tanget.

		if      ( x <= -1.0 ) y = -1.0;		// Clamp to min.
		else if ( x >=  1.0 ) y =  1.0;		// Clamp to max.
		else	
		{
			y = sin ( π÷2*x );				// Compute activation function.
		}

		// Return the result.

		return y;
	}

	//--------------------------------------------------------------------------------------------------	
	// Derivative of normalized sinusoid.
	//                   
	//                  ┌       ┐
	//          π       │ π     │
	//  f'(x) = ─ · cos │ ─ · x │
	//          2       │ 2     │
	//                  └       ┘
	//   	
	//--------------------------------------------------------------------------------------------------

	double MathML::dydx_sin_normal ( double x )
	{
		// Local constants.

		const double π   = 3.1415926535897932;
		const double π÷2 = π/2;

		// Initialize local variables.

		double dydx = 0.0;		

		// Compute normalized hyperbolic tangent.

		if      ( x <= 0.0 ) dydx = 0.0;	// Clamp to min gradient.
		else if ( x >= 1.0 ) dydx = 1.0;	// Clamp to max gradient.
		else
		{
			dydx = π÷2 * cos ( π÷2*x );		// Compute derivative.
		}

		// Return the result.

		return dydx;
	}

	//--------------------------------------------------------------------------------------------------	
	// Derivative of parameterized normalized hyperbolic tangent.
	//                   
	//   f(x) = coth(k·π)·tanh(k·π·x)
	//
	//	f'(x) = k·π·coth(k·π)·sech²(k·π·x)
	//         	
	//--------------------------------------------------------------------------------------------------

	double MathML::dydx_tanh_normal ( double x, double k )
	{
		// Local constants.

		const double π = 3.1415926535897932;

		// Declare local variables.

		double dydx = 0.0;		

		// Compute substitutions for coth(π) and sech²(k·π·x) computation.

		double kπ2   = 2*k*π;               // k multiplied by 360 degrees in radians.
		double dyu   = sinh ( kπ2 );		// coth numerator.
		double dxu   = 1-cosh ( kπ2 );		// coth denominator.
		double coth  = -dyu / dxu;			// Compute coth(2·k·π)
		double sech  = 1/cosh ( k*π*x );	// Compute hyperbolic secant.		
		double sech² = sech*sech;			// Compute sech²(k·π·x)

		// Compute normalized hyperbolic tangent.

		dydx = π*coth*sech²;				// Compute derivative.

		// Return the result.

		return dydx;
	}

	//--------------------------------------------------------------------------------------------------
	//
	//    _      n
	//  S(v)  =  ∑ ( vᵢ )
	//          i=0 
	//
	//--------------------------------------------------------------------------------------------------


	double MathML::vector_sum ( vector <double> v )
	{
		// Declare local varaibles.

		double sum = 0.0;

		// Calculate sum.

		for ( double x : v )
		{
			sum += x;
		}

		// Return the result.

		return sum;
	}

	//--------------------------------------------------------------------------------------------------
	//  _    _   _
	//  p  = u · v
	//
	//--------------------------------------------------------------------------------------------------

	vector <double> MathML::hadamard_product ( vector <double> u, vector <double> v )
	{
		// Declare local variables.

		vector <double> hp;
		double          p;
		long            u_size = u.size ();
		long            v_size = v.size ();

		// Compute the optimal array size.
		// - For safty, take the smallest one. But they 'should' both be equal size.

		int s = ( u_size < v_size ) ? u_size : v_size;

		// Make sure the two vectors are the same size.

		if ( u_size == v_size )
		{
			// Calculate the Hadamard product of vectors u and v.    

			for ( int i = 0; i < s; i++ )
			{
				p = u [ i ] * v [ i ];

				hp.push_back ( p );
			}
		}

		// Return the result. 

		return hp;
	}

	//--------------------------------------------------------------------------------------------------
	//
	//    x  =  rnd ( 0 ≤ x ≤ 1 )
	//
	//
	//          1     1         3
	// f(x)  =  ─  +  ─ (2x - 1)
	//          2     2
	//
	//--------------------------------------------------------------------------------------------------

	double MathML::gaussian_distribution ()
	{
		// Initialize random number generator.

		random_device                      rd;
		mt19937                            random_generator ( rd () );
		uniform_real_distribution <double> random_distribution ( 0.0, 1.0 );

		// Note:
		//
		// - This was ported from my Java version, and should be upgraded to take advantage of the
		//   C++11 random number library.
		//
		// - In C++11, we can generate a Gaussian distribution by using 'std::normal_distribution' from 
		//   the random number library.    

		// Compute gaussian distribution.

		double x        = random_distribution ( random_generator );
		double base     = 2 * x - 1;
		double exponent = 3;
		double y        = 0.5 + 0.5 * pow ( base, exponent );

		// Return the result.

		return y;
	}

	//--------------------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------------
}
