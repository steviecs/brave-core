/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVELEDGER_PROMOTION_TRANSFER_H_
#define BRAVELEDGER_PROMOTION_TRANSFER_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "bat/ledger/internal/credentials/credentials_factory.h"
#include "bat/ledger/ledger.h"

namespace ledger {
class LedgerImpl;

namespace promotion {

using GetEligibleTokensCallback =
    std::function<void(std::vector<type::UnblindedTokenPtr> list)>;

class PromotionTransfer {
 public:
  explicit PromotionTransfer(LedgerImpl* ledger);
  ~PromotionTransfer();

  void GetAmount(ledger::GetTransferableAmountCallback callback);

  void Start(ledger::ResultCallback callback);

 private:
  void GetEligibleTokens(GetEligibleTokensCallback callback);

  void OnGetEligiblePromotions(std::vector<type::PromotionPtr> promotions,
                               GetEligibleTokensCallback callback);

  void OnGetEligibleTokens(std::vector<type::UnblindedTokenPtr> list,
                           ledger::ResultCallback callback);

  std::vector<type::PromotionType> GetEligiblePromotions();

  LedgerImpl* ledger_;  // NOT OWNED
  std::unique_ptr<credential::Credentials> credentials_;
};

}  // namespace promotion
}  // namespace ledger

#endif  // BRAVELEDGER_PROMOTION_TRANSFER_H_
