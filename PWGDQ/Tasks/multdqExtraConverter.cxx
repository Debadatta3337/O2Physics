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

#include "Framework/runDataProcessing.h"
#include "Framework/AnalysisTask.h"
#include "Framework/AnalysisDataModel.h"
#include "PWGDQ/DataModel/ReducedInfoTables.h"
#include "Framework/ConfigParamSpec.h"
#include "Framework/HistogramRegistry.h"
#include "Framework/ASoAHelpers.h"
#include "Framework/O2DatabasePDGPlugin.h"
#include "CCDB/BasicCCDBManager.h"
#include "Common/DataModel/Multiplicity.h"
#include "Common/DataModel/EventSelection.h"
#include "Common/DataModel/TrackSelectionTables.h"
#include "TableHelper.h"
#include "MetadataHelper.h"
#include "TList.h"
#include "PWGMM/Mult/DataModel/bestCollisionTable.h"

using namespace o2;
using namespace o2::framework;

struct MultDqExtraConverter {
   Produces<aod::ReducedEventsMultPV_001> reducedEventsMultPV_001;
   void process(aod::ReducedEventsMultPV_000 const& reducedEventsMultPV_000)
   {
    for (const auto& r : reducedEventsMultPV_000) {
      reducedEventsMultPV_001(r.multNTracksHasITS(),
                     r.multNTracksHasTPC(), r.multNTracksHasTOF(), r.multNTracksHasTRD(), r.multNTracksITSOnly(),
                     r.multNTracksTPCOnly(), r.multNTracksITSTPC(), 1.0,
                     r.trackOccupancyInTimeRange());
   }
    }
};

WorkflowSpec defineDataProcessing(ConfigContext const& cfgc)
{
  return WorkflowSpec{
    adaptAnalysisTask<MultDqExtraConverter>(cfgc)};
}
