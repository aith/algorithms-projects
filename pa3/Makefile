#
# Ari Iramanesh
# airanman, 1628897
# pa3: Sparse
# cmps101, spring 2019
#
# Makefile

MAINCLASS  = Sparse
JAVAC      = javac 
JAVASRC    = $(wildcard *.java)
SOURCES    = $(JAVASRC) Makefile README
CLASSES    = $(patsubst %.java, %.class, $(JAVASRC))
JARCLASSES = $(patsubst %.class, %*.class, $(CLASSES))
JARFILE    = $(MAINCLASS) 

all: $(JARFILE)
		
$(JARFILE): $(CLASSES)
		echo Main-class: $(MAINCLASS) > Manifest
			jar cvfm $(JARFILE) Manifest $(JARCLASSES)
				chmod +x $(JARFILE)
					rm Manifest

%.class: %.java
		$(JAVAC) $<

clean:
		rm -f *.class $(JARFILE)
