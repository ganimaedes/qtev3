/**********************************************************************
 * Author:      Leo Liberti                                            *
 * Name:        auxiliary.h                                            *
 * Source:      GNU C++                                                *
 * Purpose:     prototypes for auxiliary functions in expression.cxx   *
 * History:     030121 0.0 work started                                *
 * License:     (C) Leo Liberti, all rights reserved. Code published under the
               Common Public License.
***********************************************************************/

#ifndef AUXILIARY_H
#define AUXILIARY_H

namespace Ev3
{
bool is_integer(const double);
bool is_even(const double);
bool is_odd(const double);
double Ev3NearZero();
double Ev3Infinity();
} /* namespace Ev3 */

#endif // AUXILIARY_H
