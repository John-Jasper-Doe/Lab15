/**
 * @file clusterization.hpp
 * @brief Clustering function declaration.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef CORE_CLUSTERIZATION_HPP_
#define CORE_CLUSTERIZATION_HPP_

#include <cstddef>

/** @brief The namespace of the "Clustering" project. */
namespace kkmeans {
/** @brief The namespace of the "Core" */
namespace core {

/**
 * @brief Clustering function.
 * @param [in] k - number of clusters.
 */
void clusterize(std::size_t k);

} /* core:: */
} /* kkmeans:: */

#endif /* CORE_CLUSTERIZATION_HPP_ */
