# Task Scheduler

## Description

### 問題描述

● 討論如何實作一個Task Scheduler，讓使用者可以設定定期執行多個activity job，並能查詢相關工作執行的結果
● 思考哪個部分可以設計成Thread使用，增加系統效能
<!--
幫我key一下上次整理的問題目標
-->

### 需求整理

<!--
幫我key一下上次那三個需時做出來的結果
-->
● 能夠執行多個Job
● 定期執行並利用Timer追蹤
● 查詢結果（包含狀態、時間）

## Implementation

<!--
這邊你可以試著描述一下我們怎模解決問題，這邊你盡量打就好，沒寫到的部份我週二晚會再來修
-->

● 輸入進來的有三種狀況 -
1.正常指令 2.定時指令(前面兩個args是"delay"跟秒數) 3."list"(要吐所有的proecess)
● 透過時間點紀錄是否有值來判斷執行階段，並且print出指令、狀態、runtime及turnaround time


## Usage

### 編譯方式

在terminal中執行 `make && ./main`

### 執行方式

<!--
這部份就交給你了，把如何使用都稍微描述一下
-->
<!--我clone下來時還沒有人push新的QQ 所以沒看到實際的～ 再麻煩你了！ by曉柔-->
