#ifndef OPENMC_ZPLANE_PARTITIONER_H
#define OPENMC_ZPLANE_PARTITIONER_H

#include "hdf5_interface.h"
#include "universe.h"
#include <set>
#include <vector>

namespace openmc {

using namespace std;

class ZPlanePartitioner : public UniversePartitioner {
public:
  explicit ZPlanePartitioner(const Universe& univ);
  explicit ZPlanePartitioner(const Universe& univ, hid_t file);
  virtual ~ZPlanePartitioner() override = default;

  virtual void export_to_hdf5(const std::string& file_path) const override;

  //! Return the list of cells that could contain the given coordinates.
  virtual const vector<int32_t>& get_cells(
    Position r, Direction u) const override;

private:
  //! A sorted vector of indices to surfaces that partition the universe
  vector<int32_t> surfs_;

  //! Vectors listing the indices of the cells that lie within each partition
  //
  //! There are n+1 partitions with n surfaces.  `partitions_.front()` gives the
  //! cells that lie on the negative side of `surfs_.front()`.
  //! `partitions_.back()` gives the cells that lie on the positive side of
  //! `surfs_.back()`.  Otherwise, `partitions_[i]` gives cells sandwiched
  //! between `surfs_[i-1]` and `surfs_[i]`.
  vector<vector<int32_t>> partitions_;
};

} // namespace openmc

#endif // OPENMC_ZPLANE_PARTITIONER_H