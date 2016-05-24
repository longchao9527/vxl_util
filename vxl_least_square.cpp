//
//  vxl_least_square.cpp
//  CameraPlaning
//
//  Created by Jimmy Chen LOCAL on 8/8/14.
//  Copyright (c) 2014 Nowhere Planet. All rights reserved.
//

#include "vxl_least_square.h"
#include <vnl/algo/vnl_determinant.h>
#include <vnl/vnl_sparse_matrix.h>
#include <vnl/algo/vnl_sparse_lu.h>

bool VxlLeastSquare::solver(vcl_vector<vcl_map<int, double> > & leftVec, vcl_vector<double> & rightVec,
                            bool overConstraint, int var_Num, double *result)
{
    assert(leftVec.size() == rightVec.size());
    assert(leftVec.size() >= var_Num);    
    
    vnl_sparse_matrix<double> A((int)leftVec.size(), var_Num);
   
    // set left matrix
    for (int i = 0; i<leftVec.size(); i++) {
        unsigned int sz = (unsigned int)leftVec[i].size();
        vcl_vector<int> cols(sz);
        vcl_vector<double> vals(sz);
        int j = 0;
        for (vcl_map<int, double>::iterator it = leftVec[i].begin(); it != leftVec[i].end(); it++, j++) {
            cols[j] = it->first;
            vals[j] = it->second;
        }
        A.set_row(i, cols, vals);
    }
    
    // set right vector
    vnl_vector<double> b(&rightVec[0], (int)rightVec.size());
    
    vnl_sparse_matrix<double> At = A.transpose();
    vnl_sparse_matrix<double> AtA = At * A;
    vnl_vector<double> Atb;
    At.mult(b, Atb);
    
    vnl_sparse_lu solver(AtA);
    
    vnl_vector<double> ret = solver.solve(Atb);
    assert(ret.size() == var_Num);
    for (int i = 0; i<var_Num; i++) {
        result[i] = ret[i];
    }
    return true;
}