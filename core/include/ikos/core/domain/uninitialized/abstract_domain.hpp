/*******************************************************************************
 *
 * \file
 * \brief Generic API for abstract domains keeping track of (un)initialized
 * variables
 *
 * Author: Maxime Arthaud
 *
 * Contact: ikos@lists.nasa.gov
 *
 * Notices:
 *
 * Copyright (c) 2011-2019 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Disclaimers:
 *
 * No Warranty: THE SUBJECT SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY OF
 * ANY KIND, EITHER EXPRESSED, IMPLIED, OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL CONFORM TO SPECIFICATIONS,
 * ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 * OR FREEDOM FROM INFRINGEMENT, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL BE
 * ERROR FREE, OR ANY WARRANTY THAT DOCUMENTATION, IF PROVIDED, WILL CONFORM TO
 * THE SUBJECT SOFTWARE. THIS AGREEMENT DOES NOT, IN ANY MANNER, CONSTITUTE AN
 * ENDORSEMENT BY GOVERNMENT AGENCY OR ANY PRIOR RECIPIENT OF ANY RESULTS,
 * RESULTING DESIGNS, HARDWARE, SOFTWARE PRODUCTS OR ANY OTHER APPLICATIONS
 * RESULTING FROM USE OF THE SUBJECT SOFTWARE.  FURTHER, GOVERNMENT AGENCY
 * DISCLAIMS ALL WARRANTIES AND LIABILITIES REGARDING THIRD-PARTY SOFTWARE,
 * IF PRESENT IN THE ORIGINAL SOFTWARE, AND DISTRIBUTES IT "AS IS."
 *
 * Waiver and Indemnity:  RECIPIENT AGREES TO WAIVE ANY AND ALL CLAIMS AGAINST
 * THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS, AS WELL
 * AS ANY PRIOR RECIPIENT.  IF RECIPIENT'S USE OF THE SUBJECT SOFTWARE RESULTS
 * IN ANY LIABILITIES, DEMANDS, DAMAGES, EXPENSES OR LOSSES ARISING FROM SUCH
 * USE, INCLUDING ANY DAMAGES FROM PRODUCTS BASED ON, OR RESULTING FROM,
 * RECIPIENT'S USE OF THE SUBJECT SOFTWARE, RECIPIENT SHALL INDEMNIFY AND HOLD
 * HARMLESS THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS,
 * AS WELL AS ANY PRIOR RECIPIENT, TO THE EXTENT PERMITTED BY LAW.
 * RECIPIENT'S SOLE REMEDY FOR ANY SUCH MATTER SHALL BE THE IMMEDIATE,
 * UNILATERAL TERMINATION OF THIS AGREEMENT.
 *
 ******************************************************************************/

#pragma once

#include <initializer_list>

#include <ikos/core/domain/abstract_domain.hpp>
#include <ikos/core/semantic/variable.hpp>
#include <ikos/core/value/uninitialized.hpp>

namespace ikos {
namespace core {
namespace uninitialized {

/// \brief Base class for abstract domains keeping track of (un)initialized
/// variables
template < typename VariableRef, typename Derived >
class AbstractDomain : public core::AbstractDomain< Derived > {
public:
  static_assert(
      core::IsVariable< VariableRef >::value,
      "VariableRef does not meet the requirements for variable types");

public:
  /// \brief Assign `x = initialized`
  virtual void assign_initialized(VariableRef x) = 0;

  /// \brief Assign `x = uninitialized`
  virtual void assign_uninitialized(VariableRef x) = 0;

  /// \brief Assign `x = y`
  virtual void assign(VariableRef x, VariableRef y) = 0;

  /// \brief Assign `x = f(a, b, c, ..)`
  virtual void assign(VariableRef x,
                      std::initializer_list< VariableRef > l) = 0;

  /// \brief Return true if x is initialized, otherwise false
  virtual bool is_initialized(VariableRef x) const = 0;

  /// \brief Return true if x is uninitialized, otherwise false
  virtual bool is_uninitialized(VariableRef x) const = 0;

  /// \brief Set the uninitialized value of a variable
  virtual void set(VariableRef x, const Uninitialized& value) = 0;

  /// \brief Refine the uninitialized value of a variable
  virtual void refine(VariableRef x, const Uninitialized& value) = 0;

  /// \brief Forget a variable
  virtual void forget(VariableRef x) = 0;

  /// \brief Normalize the abstract value
  virtual void normalize() const = 0;

  /// \brief Get the uninitialized value for the given variable
  virtual Uninitialized get(VariableRef x) const = 0;

}; // end class AbstractDomain

/// \brief Check if a type is an uninitialized abstract domain
template < typename T, typename VariableRef >
struct IsAbstractDomain
    : std::is_base_of< uninitialized::AbstractDomain< VariableRef, T >, T > {};

} // end namespace uninitialized
} // end namespace core
} // end namespace ikos
