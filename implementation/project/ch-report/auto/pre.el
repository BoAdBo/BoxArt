(TeX-add-style-hook
 "pre"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("fontenc" "T1")))
   (TeX-run-style-hooks
    "latex2e"
    "beamer"
    "beamer10"
    "verbatim"
    "fancyvrb"
    "xeCJK"
    "enumerate"
    "mathtools"
    "hyperref"
    "fontenc"))
 :latex)

