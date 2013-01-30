# -*- coding: utf-8 -*-
skkdic = SKKDic.new("/usr/local/share/skk/SKK-JISYO.L", "./")

puts skkdic.search("かんじ")[0]
puts skkdic.search("たのs")[0]
