/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and COPYING.LESSER.
 *
 * Copyright:     (c) 1997-2011 Lawrence Livermore National Security, LLC
 * Description:   Constant refine operator for side-centered complex data on
 *                a  mesh.
 *
 ************************************************************************/

#ifndef included_pdat_SideComplexConstantRefine
#define included_pdat_SideComplexConstantRefine

#include "SAMRAI/SAMRAI_config.h"
#include "SAMRAI/hier/Box.h"
#include "SAMRAI/hier/IntVector.h"
#include "SAMRAI/hier/Patch.h"
#include "SAMRAI/tbox/Pointer.h"
#include "SAMRAI/hier/RefineOperator.h"

#include <string>

namespace SAMRAI {
namespace pdat {

/**
 * Class SideComplexConstantRefine implements constant
 * interpolation for side-centered complex patch data defined over a
 * mesh.  It is derived from the hier::RefineOperator base class.
 * The numerical operations for interpolation use FORTRAN numerical routines.
 *
 * The findRefineOperator() operator function returns true if the input
 * variable is side-centered complex, and the string is "CONSTANT_REFINE".
 *
 * @see hier::RefineOperator
 */

class SideComplexConstantRefine:
   public hier::RefineOperator
{
public:
   /**
    * Uninteresting default constructor.
    */
   explicit SideComplexConstantRefine(
      const tbox::Dimension& dim);

   /**
    * Uninteresting virtual destructor.
    */
   virtual ~SideComplexConstantRefine();

   /**
    * Return true if the variable and name string match side-centered
    * complex constant interpolation; otherwise, return false.
    */
   bool
   findRefineOperator(
      const tbox::Pointer<hier::Variable>& var,
      const std::string& op_name) const;

   /**
    * The priority of side-centered complex constant interpolation is 0.
    * It will be performed before any user-defined interpolation operations.
    */
   int
   getOperatorPriority() const;

   /**
    * The stencil width of the constant interpolation operator is the vector
    * of zeros.  That is, its stencil does not extend outside the fine box.
    */
   hier::IntVector
   getStencilWidth() const;

   /**
    * Refine the source component on the coarse patch to the destination
    * component on the fine patch using the side-centered complex constant
    * interpolation operator.  Interpolation is performed on the intersection
    * of the destination patch and the boxes contained in fine_overlap.
    * It is assumed that the coarse patch contains sufficient data for the
    * stencil width of the refinement operator.
    */
   void
   refine(
      hier::Patch& fine,
      const hier::Patch& coarse,
      const int dst_component,
      const int src_component,
      const hier::BoxOverlap& fine_overlap,
      const hier::IntVector& ratio) const;
};

}
}
#endif