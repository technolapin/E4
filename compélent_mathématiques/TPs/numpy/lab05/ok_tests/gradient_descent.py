test = {
  'name': 'gradient_descent',
  'points': 1,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> np.random.seed(42);
          >>> 
          >>> x = np.random.rand(20);
          >>> y = 0.5*x + 2 + 0.05 * np.random.randn(20);
          >>> cost = lambda w: np.sum((w[0]*x + w[1] - y)**2);
          >>> 
          >>> w1, _ = gradient_descent(cost, w_init=[0.,0.], alpha=0.01, epochs=200);
          >>> w2, _ = gradient_descent(cost, w_init=[0.,0.], alpha=1, epochs=200, stepsize='diminishing');
          >>> 
          >>> print(w1, w2)
          [0.47524088 1.99765292] [0.47421113 1.99816154]
          """,
          'hidden': False,
          'locked': False
        }
      ],
      'scored': True,
      'setup': '',
      'teardown': '',
      'type': 'doctest'
    }
  ]
}
