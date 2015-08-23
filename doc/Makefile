ODG_FILES := $(wildcard *.odg)
PNG_FILES := $(subst odg,png,$(ODG_FILES))

all: $(PNG_FILES)

define odg_to_png

$(subst odg,png,$(1)): $(1)
	libreoffice --invisible --convert-to png --outdir ./ $$^
	mogrify -trim $$(@)
endef

$(foreach odg,$(ODG_FILES),$(eval $(call odg_to_png,$(odg))))

clean:
	rm -f $(PNG_FILES)
