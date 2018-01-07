(TeX-add-style-hook
 "document"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("linux_thesis" "twoside")))
   (add-to-list 'LaTeX-verbatim-environments-local "lstlisting")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "lstinline")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "lstinline")
   (TeX-run-style-hooks
    "latex2e"
    "chapter/titlepage"
    "chapter/c1"
    "linux_thesis"
    "linux_thesis10"
    "latexsym"
    "bm"
    "tikz"
    "listings"
    "amsmath"
    "lipsum"
    "amsfonts"
    "graphicx"
    "graphics"
    "setspace"
    "fontspec"
    "supertabular"
    "indentfirst"
    "multirow"
    "ulem")
   (TeX-add-symbols
    '("shell" 1)))
 :latex)

