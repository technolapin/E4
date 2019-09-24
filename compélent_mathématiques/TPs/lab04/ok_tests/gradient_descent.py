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
          >>> w, _ = gradient_descent(cost, w_init=[0.,0.], alpha=0.01, epochs=100);
          >>> 
          >>> print(w)
          4f25c35c5d1afc2fb7429734580f3d18
          # locked
          """,
          'hidden': False,
          'locked': True
        }
      ],
      'scored': True,
      'setup': '',
      'teardown': '',
      'type': 'doctest'
    }
  ]
}
