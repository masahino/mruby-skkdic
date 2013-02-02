# -*- coding: utf-8 -*-
skkdic_s = SKKDic.new("/usr/local/share/skk/SKK-JISYO.S")
skkdic_m = SKKDic.new("/usr/local/share/skk/SKK-JISYO.M")
skkdic_l = SKKDic.new("/usr/local/share/skk/SKK-JISYO.L")

puts skkdic_s.search("かんじ")[0]
puts skkdic_s.search("かん")[0]
puts skkdic_s.search("か")[0]
puts skkdic_s.search("たのs")[0]
puts skkdic_s.search("よろs")[0]

puts skkdic_m.search("かんじ")[0]
puts skkdic_m.search("かん")[0]
puts skkdic_m.search("か")[0]
puts skkdic_m.search("たのs")[0]
puts skkdic_s.search("よろs")[0]

puts skkdic_l.search("かんじ")[0]
puts skkdic_l.search("かん")[0]
puts skkdic_l.search("か")[0]
puts skkdic_l.search("たのs")[0]
puts skkdic_s.search("よろs")[0]
