# -*- coding: utf-8 -*-
assert('mruby-skkdic 1') do
  skkdic = SKKDic.new("foo/bar/baz")
end

assert('mruby-skkdic 2') do
  skkdic = SKKDic.new("mruby-skkdic/test/test-jisyo.txt")
  skkdic.search('をs') == ['惜']
  skkdic.search('ふるいたc') == ['奮い立', '奮い起']
  skkdic.search('さきn') == ['先']
  skkdic.search('#はく#か') == ['#3泊#3日']
  skkdic.search('>まよw') == ['迷']
  skkdic.search('allelopathy') == ['アレロパシー']
  skkdic.search('しゅじ') == ['主事', '朱字', '主辞;head-word', '主餌']
  skkdic.search('そつぎょうご') == ['卒業後']
end

assert('mruby-skkdic 3') do
  skkdic = SKKDic.new("mruby-skkdic/test/test-jisyo.txt")
  skkdic.is_okuri_ari('') == false
  skkdic.is_okuri_ari('ruby') == false
  skkdic.is_okuri_ari('あるk') == false
end

assert('mruby-skkdic 4') do
  skkdic = SKKDic.new("mruby-skkdic/test/test-jisyo.txt")
  skkdic.respond_to? :to_s
end
