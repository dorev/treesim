# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Git/treesim/external/glm/src/glm"
  "D:/Git/treesim/external/glm/src/glm-build"
  "D:/Git/treesim/external/glm"
  "D:/Git/treesim/external/glm/tmp"
  "D:/Git/treesim/external/glm/src/glm-stamp"
  "D:/Git/treesim/external/glm/src"
  "D:/Git/treesim/external/glm/src/glm-stamp"
)

set(configSubDirs Debug;Release;MinSizeRel;RelWithDebInfo)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Git/treesim/external/glm/src/glm-stamp/${subDir}")
endforeach()
