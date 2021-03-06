// Copyright (c) 2010-2014, The Video Segmentation Project
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the The Video Segmentation Project nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// ---

#ifndef FVS_FACE_REGIONS_H__
#define FVS_FACE_REGIONS_H__


#include "face_video_segment.pb.h"

// std
#include <memory>

// sfl
#include <sfl/sequence_face_landmarks.h>

// segmentation
#include <segment_util/segmentation.pb.h>

// OpenCV
#include <opencv2/core.hpp>

namespace fvs {

    /** @brief Classifies segmented regions into face region types.
    The face region types are:
    - Empty - The Region does not participate in the face segmentation.
    - Full - The entire region is taken as part of the face segmentation.
    - Intersection - Only the intersection of the region with the face's
    contours is taken as part of the face segmentation.
    */
    class FaceRegions
    {
    public:
        /** @brief Constructor.
        */
        FaceRegions();

        /** @brief Add a new frame.
        @param[in] seg_desc Segmentation descriptor.
        @param[in] sfl_frame Landmarks frame.
        @param[in,out] fvs_frame Regions frame.
        */
        void addFrame(const segmentation::SegmentationDesc& seg_desc, 
            const sfl::Frame& sfl_frame, Frame& fvs_frame);

    private:
        /** @brief Add a new face.
        @param[in] sfl_face Landmarks face.
        @param[in,out] fvs_frame Regions frame.
        */
        void addFace(const segmentation::SegmentationDesc& seg_desc,
            const sfl::Face& sfl_face, Frame& fvs_frame);

        /** @brief Fill the inside face contours to create a face mask.
        */
        cv::Mat createFaceMap(const cv::Size& size, const std::vector<cv::Point>& landmarks);

        // Holds the segmentation for the current chunk.
        std::unique_ptr<segmentation::SegmentationDesc> m_seg_hier;
    };

}  // namespace fvs

#endif  // FVS_FACE_REGIONS_H__
