/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkPowImageFilter.h,v $
  Language:  C++
  Date:      $Date: 2008-10-16 19:33:41 $
  Version:   $Revision: 1.26 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkPowImageFilter_h
#define __itkPowImageFilter_h

#include "itkBinaryFunctorImageFilter.h"

namespace itk
{
  
/** \class PowImageFilter
 * \brief Compute the pow of the pixels in the first input by the pixels in the second one.
 *
 * This class is parametrized over the types of the two 
 * input images and the type of the output image. 
 * Numeric conversions (castings) are done by the C++ defaults.
 * 
 * \author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
 *
 * \ingroup IntensityImageFilters  Powithreaded
 */
namespace Function {  

template< class TInput1, class TInput2=TInput1, class TOutput=TInput1>
class Pow
{
public:
  Pow() {}
  ~Pow() {}
  bool operator!=( const Pow & ) const
    {
    return false;
    }
  bool operator==( const Pow & other ) const
    {
    return !(*this != other);
    }
  inline TOutput operator()( const TInput1 & A, const TInput2 & B)
    {
    return static_cast<TOutput>( vcl_pow( (double)A, (double)B ) );
    }
}; 
}

template <class TInputImage1, class TInputImage2=TInputImage1, class TOutputImage=TInputImage1>
class ITK_EXPORT PowImageFilter :
    public
BinaryFunctorImageFilter<TInputImage1,TInputImage2,TOutputImage, 
                         Function::Pow< 
  typename TInputImage1::PixelType, 
  typename TInputImage2::PixelType,
  typename TOutputImage::PixelType>   >
{
public:
  /** Standard class typedefs. */
  typedef PowImageFilter       Self;
  typedef BinaryFunctorImageFilter<TInputImage1,TInputImage2,TOutputImage, 
                                   Function::Pow< 
    typename TInputImage1::PixelType, 
    typename TInputImage2::PixelType,
    typename TOutputImage::PixelType>   
  >                                 Superclass;
  typedef SmartPointer<Self>        Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(PowImageFilter, 
               BinaryFunctorImageFilter);

protected:
  PowImageFilter() {}
  virtual ~PowImageFilter() {}

private:
  PowImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};

} // end namespace itk


#endif
