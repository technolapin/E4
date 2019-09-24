test = {
  'name': 'relu_model',
  'points': 1,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> np.random.seed(42);
          >>> 
          >>> B = 5;
          >>> N = 2;
          >>> P = 4;
          >>> w = np.random.randn((N+2)*B+1);
          >>> x = np.random.randn(P,N);
          >>> 
          >>> relu_model(x, w)
          array([-3.65105119, -6.22539588, -4.34448469, -3.79607935])
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
