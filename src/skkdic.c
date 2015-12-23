#include <mruby.h>
#include <mruby/string.h>
#include <mruby/array.h>
#include <mruby/variable.h>
#include <stdio.h>
#include <string.h>

static mrb_value
mrb_skkdic_dict_data(mrb_state *mrb, mrb_value self)
{
     mrb_value path, block, argv[4], table;
     char line[2048], *cstr, *p;
     int okuri_pos = 0;
     FILE *f;
     int i = 0;

     mrb_get_args(mrb, "&S", &block, &path);
     f = fopen(RSTRING_PTR(path), "r");
     if (f == NULL) {
	  puts("file open error\n");
     } else {
	  while(fgets(line, sizeof(line), f) != NULL) {
	       int ai = mrb_gc_arena_save(mrb);
	       if (strcmp(line, ";; okuri-ari entries.\n") == 0) {
		    okuri_pos++;
		    continue;
	       }
	       if (strcmp(line, ";; okuri-nasi entries.\n") == 0) {
		    okuri_pos++;
		    continue;
	       }
	       if (line[0] == ';') {
		    continue;
	       }
	       cstr = strtok(line, " ");
	       argv[1] = mrb_str_new_cstr(mrb, cstr);
	       cstr = strtok(NULL, " ");
	       p = strtok(cstr, "/");

	       table = mrb_ary_new(mrb);
	       while (p != NULL) {
		    int ai2 = mrb_gc_arena_save(mrb);
		    mrb_ary_push(mrb, table, mrb_str_new_cstr(mrb, p));
		    p = strtok(NULL, "/");
		    mrb_gc_arena_restore(mrb, ai2);
	       }
	       mrb_ary_pop(mrb, table);
	       argv[2] = table;
	       if (okuri_pos == 1) {
		    // okuri_ari
		    argv[0] = mrb_fixnum_value(0);
		    mrb_yield_argv(mrb, block, 3,
				   argv);
	       } else if(okuri_pos == 2) {
		    // okuri_nasi
		    argv[0] = mrb_fixnum_value(1);
		    mrb_yield_argv(mrb, block, 3,
				   argv);

	       }
	       mrb_gc_arena_restore(mrb, ai);
	  }
     }
     return self;
}


static mrb_value
mrb_skkdic_make_table(mrb_state *mrb, mrb_value self)
{
     mrb_value path;
     mrb_value okuri_ari_table, okuri_nasi_table;
     FILE *f;
     char line[2048];
     int okuri_pos = 0;

     mrb_get_args(mrb, "S", &path);

     okuri_ari_table = mrb_ary_new(mrb);
     okuri_nasi_table = mrb_ary_new(mrb);

     f = fopen(RSTRING_PTR(path), "r");
     if (f == NULL) {
	  puts("file open error\n");
     } else {
	  while(fgets(line, sizeof(line), f) != NULL) {
//	       mrb_value s;
//	       printf("%d arena_idx = %d\n", i++, mrb->arena_idx);
	       int ai = mrb_gc_arena_save(mrb);
	       if (strcmp(line, ";; okuri-ari entries.\n") == 0) {
		    okuri_pos++;
		    continue;
	       }
	       if (strcmp(line, ";; okuri-nasi entries.\n") == 0) {
		    okuri_pos++;
		    continue;
	       }
	       if (okuri_pos == 1) {
		    // okuri_ari
		    mrb_ary_push(mrb, okuri_ari_table,
				 mrb_str_new_cstr(mrb, line));
	       } else if(okuri_pos == 2) {
		    // okuri_nasi
		    mrb_ary_push(mrb, okuri_nasi_table,
				 mrb_str_new_cstr(mrb, line));
	       }
	       mrb_gc_arena_restore(mrb, ai);
	  }
     }
     mrb_iv_set(mrb, self, 
		mrb_intern_lit(mrb, "@okuri_ari_table"), okuri_ari_table);
     mrb_iv_set(mrb, self, 
		mrb_intern_lit(mrb, "@okuri_nasi_table"), okuri_nasi_table);
     return self;
}

void
mrb_mruby_skkdic_gem_init(mrb_state* mrb) {
     struct RClass *skkdic = mrb_define_class(mrb, "SKKDic", mrb->object_class);
     mrb_define_method(mrb, skkdic, "make_table", 
		       mrb_skkdic_make_table, MRB_ARGS_REQ(1));
     mrb_define_method(mrb, skkdic, "dict_data", 
		       mrb_skkdic_dict_data, MRB_ARGS_REQ(2));
}

void
mrb_mruby_skkdic_gem_final(mrb_state* mrb) {
  // finalizer
}
