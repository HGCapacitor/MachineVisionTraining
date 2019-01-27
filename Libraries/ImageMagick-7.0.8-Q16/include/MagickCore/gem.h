/*
  Copyright 1999-2019 ImageMagick Studio LLC, a non-profit organization
  dedicated to making software imaging solutions freely available.
  
  You may not use this file except in compliance with the License.
  obtain a copy of the License at
  
    https://imagemagick.org/script/license.php
  
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  MagickCore graphic gems methods.
*/
#ifndef MAGICKCORE_GEM_H
#define MAGICKCORE_GEM_H

#include "MagickCore/fx.h"
#include "MagickCore/random_.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern MagickExport double
  ExpandAffine(const AffineMatrix *);

extern MagickExport void
  ConvertHSLToRGB(const double,const double,const double,double *,double *,
    double *),
  ConvertRGBToHSL(const double,const double,const double,double *,double *,
    double *);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
