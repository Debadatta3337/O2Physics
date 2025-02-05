// Copyright 2019-2020 CERN and copyright holders of ALICE O2.
// See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
// All rights not expressly granted are reserved.
//
// This software is distributed under the terms of the GNU General Public
// License v3 (GPL Version 3), copied verbatim in the file "COPYING".
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.
//
// Contact: iarsene@cern.ch, i.c.arsene@fys.uio.no
//
// Task used to convert the data model from the old format to the new format. To avoid
// the conflict with the old data model.

// other includes
#include "Framework/runDataProcessing.h"
#include "Framework/AnalysisTask.h"
#include "Framework/AnalysisDataModel.h"
#include "Framework/AnalysisHelpers.h"
#include "Framework/Configurable.h"
#include "Framework/WorkflowSpec.h"
#include "PWGDQ/DataModel/ReducedInfoTables.h"

struct MultPVConverter000_001 {
  Produces<o2::aod::ReducedEventsMultPV_001> multPV_001;
  void process(o2::aod::ReducedEventsMultPV_001 const& multsPV)
  {
    for (const auto& r : multsPV) {
      multPV_001(r.multNTracksHasITS(), r.multNTracksHasTPC(), r.multNTracksHasTOF(), r.multNTracksHasTRD(),
                     r.multNTracksITSOnly(), r.multNTracksTPCOnly(), r.multNTracksITSTPC(), r.numTrnacksInTimeRange(), -999.);
    }
  }

  void processDummy(o2::aod::ReducedEvents&)
  {
    // do nothing
  }

  PROCESS_SWITCH(MultPVConverter000_001, process, "Convert Table MultPV_000 to Table MultPV_001", false);
  PROCESS_SWITCH(MultPVConverter000_001, processDummy, "do nothing", false);
};

WorkflowSpec defineDataProcessing(ConfigContext const& cfgc)
{
  return WorkflowSpec{
    adaptAnalysisTask<MultPVConverter000_001>(cfgc)};
}
