/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_ADS_INTERNAL_AD_REWARDS_PAYMENTS_PAYMENTS_H_
#define BAT_ADS_INTERNAL_AD_REWARDS_PAYMENTS_PAYMENTS_H_

#include <stdint.h>

#include <string>

#include "base/time/time.h"
#include "base/values.h"
#include "bat/ads/internal/account/ad_rewards/payments/payment_info.h"

namespace ads {

class Payments {
 public:
  Payments();

  ~Payments();

  bool SetFromJson(
      const std::string& json);
  bool SetFromDictionary(
      base::Value* dictionary);
  base::Value GetAsList();

  double GetBalance() const;

  bool DidReconcileBalance(
      const double balance,
      const double unreconciled_estimated_pending_rewards) const;

  base::Time CalculateNextPaymentDate(
      const base::Time& time,
      const base::Time& token_redemption_date) const;

  PaymentInfo GetForThisMonth(
      const base::Time& time) const;

 private:
  PaymentList payments_;

  PaymentList GetFromList(
      base::ListValue* list) const;

  bool GetBalanceFromDictionary(
      base::DictionaryValue* dictionary,
      double* balance) const;
  bool GetMonthFromDictionary(
      base::DictionaryValue* dictionary,
      std::string* month) const;
  bool GetTransactionCountFromDictionary(
      base::DictionaryValue* dictionary,
      uint64_t* transaction_count) const;

  bool HasPendingBalanceForTransactionMonth(
      const std::string& month) const;

  PaymentInfo GetPaymentForTransactionMonth(
      const std::string& month) const;

  std::string GetTransactionMonth(
      const base::Time& time) const;
  std::string GetPreviousTransactionMonth(
      const base::Time& time) const;

  std::string GetFormattedTransactionMonth(
      const int year,
      const int month) const;
};

}  // namespace ads

#endif  // BAT_ADS_INTERNAL_AD_REWARDS_PAYMENTS_PAYMENTS_H_
