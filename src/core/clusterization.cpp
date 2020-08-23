#include "clusterization.hpp"

#include <dlib/clustering.h>
#include <dlib/rand.h>

#include <iostream>
#include <istream>
#include <vector>

/** @brief The namespace of the "Clustering" project. */
namespace kkmeans {
/** @brief The namespace of the "Core" */
namespace core {

/** @brief Anonymous namespace. */
namespace {

// Here we declare that our samples will be 2 dimensional column vectors.
// (Note that if you don't know the dimensionality of your vectors at compile time
// you can change the 2 to a 0 and then set the size at runtime)
using sample_type = dlib::matrix<double, 2, 1>;

// Now we are making a typedef for the kind of kernel we want to use.  I picked the
// radial basis kernel because it only has one parameter and generally gives good
// results without much fiddling.
using kernel_type = dlib::radial_basis_kernel<sample_type>;

/**
 * @brief Reading data from an input stream.
 *
 * @details
 * Data is received from the input stream, then read line by line, parsed and
 * formed into a data vector.
 *
 * @param [in] istrm - the input stream where the data comes from.
 * @return Data vector ready.
 */
std::vector<sample_type> read_from(std::istream& istrm) {
  std::vector<sample_type> res;

  while (istrm) {
    std::string line;
    istrm >> line;

    if (!line.empty()) {
      sample_type dot;
      std::size_t sep_pos = line.find(';');
      dot(0) = std::stod(line.substr(0, sep_pos));
      dot(1) = std::stod(line.substr(sep_pos + 1, line.size() - sep_pos - 1));
      res.push_back(std::move(dot));
    }
  }

  return res;
}

} /* :: */

/* Clustering function */
void clusterize(std::size_t k) {
  // Here we declare an instance of the kcentroid object.  It is the object used to
  // represent each of the centers used for clustering.  The kcentroid has 3 parameters
  // you need to set.  The first argument to the constructor is the kernel we wish to
  // use.  The second is a parameter that determines the numerical accuracy with which
  // the object will perform part of the learning algorithm.  Generally, smaller values
  // give better results but cause the algorithm to attempt to use more dictionary vectors
  // (and thus run slower and use more memory).  The third argument, however, is the
  // maximum number of dictionary vectors a kcentroid is allowed to use.  So you can use
  // it to control the runtime complexity.
  dlib::kcentroid<kernel_type> kc(kernel_type(0.000001), 0.01, 16);

  // Now we make an instance of the kkmeans object and tell it to use kcentroid objects
  // that are configured with the parameters from the kc object we defined above.
  dlib::kkmeans<kernel_type> test(kc);

  std::vector<sample_type> samples = read_from(std::cin);
  std::vector<sample_type> initial_centers;

  // tell the kkmeans object we made that we want to run k-means with k clusters
  test.set_number_of_centers(k);

  // You need to pick some initial centers for the k-means algorithm.  So here
  // we will use the dlib::pick_initial_centers() function which tries to find
  // n points that are far apart (basically).
  pick_initial_centers(static_cast<long>(k), initial_centers, samples, test.get_kernel());

  // now run the k-means algorithm on our set of samples.
  test.train(samples, initial_centers);

  // now loop over all our samples and print out their predicted class.  In this example
  // all points are correctly identified.
  for (auto& point : samples) {
    std::cout << point(0) << ';' << point(1) << ';' << test(point) << '\n';
  }
}

} /* core:: */
} /* kkmeans:: */
