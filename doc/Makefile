
report:
	pdflatex report.tex

run:
	evince report.pdf
clean:
	rm -f report.toc report.out report.aux report.log parse-tree.toc parse-tree.aux parse-tree.log

parse_tree:
	pdflatex parse-tree.tex

uml_convert:
	#save in .eps then convert it with this
	epstopdf uml.eps
