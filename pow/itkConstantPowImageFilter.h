/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkConstantPowImageFilter.h,v $
  Language:  C++
  Date:      $Date: 2008-08-11 21:18:10 $
  Version:   $Revision: 1.3 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __itkConstantPowImageFilter_h
#define __itkConstantPowImageFilter_h

#include "itkUnaryFunctorImageFilter.h"
#include "itkNumericTraits.h"

namespace itk
{
  
/** \class ConstantPowImageFilter
 *
 * \brief Compute the pow of the input pixels at a constant
 *
 * This filter is templated over the input image type
 * and the output image type.
 *
 * \author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
 *
 * \ingroup IntensityImageFilters  Multithreaded
 * \sa UnaryFunctorImageFilter
 */
namespace Functor {  
  
template< class TInput, class TConstant, class TOutput>
class ConstantPow
{
public:
  ConstantPow() : m_Constant(NumericTraits<TConstant>::One) {};
  ~ConstantPow() {};
  bool operator!=( const ConstantPow & other ) const
    {
    return !(*this == other);
    }
  bool operator==( const ConstantPow & other ) const
    {
    return other.m_Constant == m_Constant;
    }
  inline TOutput operator()( const TInput & A )
    {
    return static_cast<TOutput>( vcl_pow( (double)A, (double)m_Constant ) );
    }
  void SetConstant(TConstant ct) {this->m_Constant = ct; }
  const TConstant & GetConstant() const { return m_Constant; }
  
  TConstant m_Constant;
};
}

template <class TInputImage, class TConstant=double, class TOutputImage=TInputImage>
class ITK_EXPORT ConstantPowImageFilter :
      public
UnaryFunctorImageFilter<TInputImage,TOutputImage, 
                        Functor::ConstantPow< 
   typename TInputImage::PixelType, TConstant,
   typename TOutputImage::PixelType> >
{
public:
  /** Standard class typedefs. */
  typedef ConstantPowImageFilter                 Self;
  typedef UnaryFunctorImageFilter<
    TInputImage,TOutputImage, 
    Functor::ConstantPow< 
      typename TInputImage::PixelType, TConstant,
      typename TOutputImage::PixelType>   >             Superclass;
  typedef SmartPointer<Self>                            Pointer;
  typedef SmartPointer<const Self>                      ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ConstantPowImageFilter, UnaryFunctorImageFilter);

  
  /** Set the constant that will be used to multiply all the image pixels */
  void SetConstant(TConstant ct)
    {
    if( ct != this->GetFunctor().GetConstant() )
      {
      this->GetFunctor().SetConstant(ct);
      this->Modified();
      }
    }
  const TConstant & GetConstant() const
    {
    return this->GetFunctor().GetConstant();
    }
  
protected:
  ConstantPowImageFilter() {};
  virtual ~ConstantPowImageFilter() {};
   
  void PrintSelf(std::ostream &os, Indent indent) const
    {
    Superclass::PrintSelf(os, indent);
    os << indent << "Constant: " 
       << static_cast<typename NumericTraits<TConstant>::PrintType>(this->GetConstant())
       << std::endl;
    }

private:
  ConstantPowImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};


} // end namespace itk

#endif
