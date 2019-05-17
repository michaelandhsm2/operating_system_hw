# Unpack Encrypted Zip

## Analyze problems of false positive

- 有1：256的概率會在給錯誤密碼時，通過了header test，進而顯示該密碼為正確的，然而因提取數據生成錯誤的CRC，所以仍無法解壓縮
- 這其實是PKWARE zipfile的一個安全功能，有助於防止像這次作業要求的暴力破解

# Task Scheduler

## Description

### 問題描述

- 討論如何實作一個Task Scheduler，讓使用者可以設定定期執行多個activity job，並能查詢相關工作執行的結果
- 思考哪個部分可以設計成Thread使用，增加系統效能

### 需求整理

- 能夠執行多個Job
- 定期執行並利用Timer追蹤
- 查詢結果（包含狀態、時間）

## Implementation

- 輸入進來的有三種狀況 -
  1.正常指令
  2.定時指令(delay)
  3."list"(要吐所有的proecess)
- 透過時間點紀錄是否有值來判斷執行階段，並且print出指令、狀態、runtime及turnaround time

## Usage

### 編譯、執行方式

在terminal中執行 `make && ./main`
