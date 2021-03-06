//
//  vil_plus_extra.h
//  GenerateFeature
//
//  Created by jimmy on 2016-07-22.
//  Copyright (c) 2016 Nowhere Planet. All rights reserved.
//

#ifndef __GenerateFeature__vil_plus_extra__
#define __GenerateFeature__vil_plus_extra__

// functions need private library from Disney Research

#include <stdio.h>
#include <vil/vil_image_view.h>
#include <vil/vil_load.h>
#include <vcl_vector.h>
#include <vgl/algo/vgl_h_matrix_2d.h>
#include <vpgl/vpgl_perspective_camera.h>
#include <vgl/vgl_point_2d.h>
#include <vgl/vgl_point_3d.h>
#include <vgl/vgl_line_segment_3d.h>
#include <vgl/vgl_ellipse_2d.h>
#include <vicl/vicl_ellipse.h>
#include <vil/vil_quantize.h>
#include <vgl/vgl_intersection+.h>
#include <vpgl/algo/vpgl_calibration_matrix_compute.h>
#include <vicl/vicl_line_segment.h>
#include <vil/vil_interp.h>
#include <vil/vil_correlation.h>
#include <vgl/vgl_transform_2d.h>
#include <vicl/vicl_ellipse.h>
#include <vicl/vicl_colours.h>

class VilPlusExtra
{
public:
    static void vil_save(const vil_image_view<double> & image, char const* filename, bool print_logo = true);
    static void vil_save(const vil_image_view<int> & image, char const* filename, bool print_logo = true);
    
    // no smooth
    static void vil_magnitude(const vil_image_view<double> &image, vil_image_view<double> &magnitude);
    static void vil_magnitude(const vil_image_view<vxl_byte> & image, vil_image_view<double> &magnitude);
    
    static void vil_gradient(const vil_image_view<vxl_byte> & image, vil_image_view<double> & magnitude,
                             vil_image_view<double> & grad_i, vil_image_view<double> & grad_j, bool smooth = false);
    
    // gaussian smooth before gradient
    static void vil_smooth_gradient(const vil_image_view<vxl_byte> & image, vil_image_view<double> & magnitude,
                                    vil_image_view<double> & grad_i, vil_image_view<double> & grad_j);
    
    // sum of squared distance between gradient
    static double vil_gradient_ssd(const vil_image_view<vxl_byte> &image1, const vil_image_view<vxl_byte> & image2);
    
    static void draw_ellipse(vil_image_view<vxl_byte> & image, const vgl_ellipse_2d<double> & ellipse, const vcl_vector<vxl_byte> & colour);
    
    static void draw_circle(vil_image_view<vxl_byte> & image, const vcl_vector< vgl_point_2d<double> > & pts,
                            int radius, const vcl_vector<vxl_byte> & colour);
    
    // draw the direction of velocity
    static void draw_velocity(vil_image_view<vxl_byte> & image, const vcl_vector< vgl_point_2d<double> > & pts,
                              const vcl_vector< vnl_vector_fixed<double, 2> > & vlt,
                              double scale, const vcl_vector<vxl_byte> & colour);
    
    // scale
    // orientation: radians between x axis
    static void draw_covariance(vil_image_view<vxl_byte> & image,
                                const vnl_matrix_fixed<double, 2, 2> & cov,
                                const vgl_point_2d<double> & loc,
                                double orientation, const vcl_vector<vxl_byte> & colour,
                                double scale = 3.0);
};

#endif /* defined(__GenerateFeature__vil_plus_extra__) */
