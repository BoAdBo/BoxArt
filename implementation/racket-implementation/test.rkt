#lang racket

(provide (all-defined-out))

(define (count-string target corpus)
  ;; target is string list
  ;; corpus, where count the occurrence of target in corpus

  ;; Algorithm:
  ;; 1. match target until it reaches null, add one to count and move to corpus next word
  ;; 2. if target doesn't match, move to corpus next word
  ;; 3. end at corpus null
  (letrec (
           ;; match-target match target to a sub-string of corpus.
           ;; return true if target reach the end(meaning the previous words of target all match)
           ;; 
           [match-target (lambda (tar cor)
                           (if (null? tar)
                               #t
                               (if (null? cor)
                                   #f
                                   (if (equal? (car tar) (car cor))
                                       (match-target (cdr tar) (cdr cor))
                                       #f))))]
           [next-corpus (lambda (cor count)
                          (if (null? cor)
                              count
                              (if (match-target target cor)
                                  (next-corpus (cdr cor) (+ count 1))
                                  (next-corpus (cdr cor) count))))])
    (next-corpus (target 0))))
